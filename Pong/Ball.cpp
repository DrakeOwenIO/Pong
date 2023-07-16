#include "Ball.h"

Ball::Ball() {
	speed = INITIAL_SPEED;


	pos.x = 0;


	pos.x = SCREEN_WIDTH / 2 - size / 2;
	pos.y = SCREEN_HEIGHT / 2 - size / 2;

	vel.x = -1;
	vel.y = 1;

	rect.x = (int)pos.x;
	rect.y = (int)pos.y;
	rect.w = size;
	rect.h = size;

	sound = Mix_LoadWAV("Assets/pong.wav");
}

void Ball::Update(Paddle* lPaddle, Paddle* rPaddle) {
	pos.x = pos.x + vel.x * speed;
	pos.y = pos.y + vel.y * speed;

	// Reset ball if you miss
	if (pos.x < 0 || pos.x > SCREEN_WIDTH - size) {
		Reset();
	}

	// Bounce when you hit the paddle
	HandleCollision(lPaddle);
	HandleCollision(rPaddle);

	// Keep ball in bounds
	if (pos.y < 0) {
		pos.y = 0;
		vel.y *= -1;
	}
	else if (pos.y + size > SCREEN_HEIGHT) {
		pos.y = SCREEN_HEIGHT - size;
		vel.y *= -1;
	}

	rect.x = (int)pos.x;
	rect.y = (int)pos.y;
}

bool Ball::TopCollision(Paddle* paddle) {
	bool passedBoundary = false;
	bool collided = false;

	if (paddle->GetId() == 0) {
		passedBoundary = pos.x < size;
	}
	else if (paddle->GetId() == 1) {
		passedBoundary = pos.x > SCREEN_WIDTH - size;
	}

	if (passedBoundary &&
		pos.y + size >= paddle->GetRect()->y &&					// Passed outer boundary of paddle
		pos.y < paddle->GetRect()->y &&							// Bottom of ball is inside top of paddle
		vel.y < 0) {											// Top of ball is not inside top of paddle
		pos.y = paddle->GetRect()->y - size - 1;				// Ball is moving down
		vel.y *= -1;											// Give a buffer of 1px so doesn't intersect immediately
		rect.y = pos.y;

		collided = true;
	}

	return collided;
}

bool Ball::BottomCollision(Paddle* paddle) {
	bool passedBoundary = false;
	bool collided = false;

	if (paddle->GetId() == 0) {
		passedBoundary = pos.x < size;
	}
	else if (paddle->GetId() == 1) {
		passedBoundary = pos.x > SCREEN_WIDTH - size;
	}

	if (passedBoundary &&
		pos.y <= paddle->GetRect()->y + paddle->GetRect()->h &&					// Passed outer boundary of paddle
		pos.y + size > paddle->GetRect()->y + paddle->GetRect()->h &&			// Top of ball is inside bottom of paddle
		vel.y < 0) {															// Bottom of ball is not inside bottom of paddle
		pos.y = paddle->GetRect()->y + paddle->GetRect()->h + 1;				// Ball is moving up
		vel.y *= -1;															// Give a buffer of 1px so doesn't intersect immediately
		rect.y = pos.y;

		collided = true;
	}

	return collided;
}

void Ball::HandleCollision(Paddle* paddle) {
	if (BottomCollision(paddle) || TopCollision(paddle)) {
		Mix_PlayChannel(-1, sound, 0);
		return;
	}

	if (pos.x + size >= paddle->GetPos().x &&									// Right ball intersect left paddle
		pos.x <= paddle->GetPos().x + paddle->GetRect()->w &&					// Left ball intersect right paddle
		pos.y + size >= paddle->GetPos().y &&									// Bottom aball intersect top paddle
		pos.y <= paddle->GetPos().y + paddle->GetRect()->h						// Top ball intersect bottom paddle
		){
		vel.x *= -1;

		// Bounce ball differently depending on where it hits the paddle
		int middlePaddleY = paddle->GetPos().y + paddle->GetRect()->h / 2;
		int middeBallY = pos.y + size / 2;
		int offsetY = middlePaddleY - middlePaddleY;

		vel.y -= offsetY * 1.5 / 100.f;

		if (paddle->GetId() == 0) {
			pos.x = paddle->GetPos().x + paddle->GetRect()->w;
		}
		else if (paddle->GetId() == 1) {
			pos.x = paddle->GetPos().x - size;
		}

		Mix_PlayChannel(-1, sound, 0);

		// Increases speed with each paddle hit
		if (speed < MAX_SPEED) {
			speed++;
		}
	}
}

SDL_Rect* Ball::GetRect() {
	return &rect;
}

void Ball::Shutdown() {
	Mix_FreeChunk(sound);
}

void Ball::Reset() {
	speed = INITIAL_SPEED;

	pos.x = SCREEN_WIDTH / 2 - size / 2;
	pos.y = SCREEN_HEIGHT / 2 - size / 2;

	rect.x = (int)pos.x;
	rect.y = (int)pos.y;
}