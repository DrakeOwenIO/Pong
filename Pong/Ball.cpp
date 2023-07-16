#include "Ball.h"



Ball::Ball() {
	speed = 0.15;


	pos.x = 0;


	pos.x = SCREEN_WIDTH / 2 - size / 2;
	pos.y = SCREEN_HEIGHT / 2 - size / 2;

	vel.x = 1;
	vel.y = 1;

	rect.x = (int)pos.x;
	rect.y = (int)pos.y;
	rect.w = size;
	rect.h = size;
}

void Ball::Update(Paddle* lPaddle, Paddle* rPaddle) {
	pos.x = pos.x + vel.x * speed;
	pos.y = pos.y + vel.y * speed;

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

void Ball::SetVel(float x, float y) {

}

void Ball::InvertXVel() {
	
}

void Ball::HandleCollision(Paddle* paddle) {
	if (pos.x + size >= paddle->GetPos().x && // Right ball intersect left paddle
		pos.x <= paddle->GetPos().x + paddle->GetRect()->w && // Left ball intersect right paddle
		pos.y + size >= paddle->GetPos().y && // Bottom aball intersect top paddle
		pos.y <= paddle->GetPos().y + paddle->GetRect()->h // Top ball intersect bottom paddle
		){
		vel.x *= -1;

		if (paddle->GetId() == 0) {
			pos.x = paddle->GetPos().x + paddle->GetRect()->w;
		}
		else if (paddle->GetId() == 1) {
			pos.x = paddle->GetPos().x - size;
		}
	}
}

SDL_Rect* Ball::GetRect() {
	return &rect;
}