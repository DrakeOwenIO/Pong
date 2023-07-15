#include "Ball.h"



Ball::Ball() {
	speed = 0.10;


	pos.x = 0;


	pos.x = SCREEN_WIDTH / 2 - size / 2;
	pos.y = SCREEN_HEIGHT / 2 - size / 2;

	vel.x = 1;
	vel.y = 0;

	rect.x = (int)pos.x;
	rect.y = (int)pos.y;
	rect.w = size;
	rect.h = size;
}

void Ball::Update() {
	pos.x = pos.x + vel.x * speed;
	pos.y = pos.y + vel.y * speed;

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
	vel.x *= -1;
}

bool Ball::HasCollided(Paddle* paddle) {
	if (pos.x + size >= paddle->GetPos().x && // Right ball intersect left paddle
		pos.x <= paddle->GetPos().x + paddle->GetRect()->w && // Left ball intersect right paddle
		pos.y + size >= paddle->GetPos().y && // Bottom aball intersect top paddle
		pos.y <= paddle->GetPos().y + paddle->GetRect()->h // Top ball intersect bottom paddle
		){
			return true;
		}
		return false;
}

SDL_Rect* Ball::GetRect() {
	return &rect;
}