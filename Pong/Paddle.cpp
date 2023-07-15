#include "Paddle.h"
#include "Utils.h"

Paddle::Paddle(int i) {
	id = i;
	speed = 0.25;

	if (id == 0) {
		pos.x = 0;
	}
	else if (id == 1) {
		pos.x = SCREEN_WIDTH - width;
	}

	pos.y = SCREEN_HEIGHT / 2 - height / 2;

	rect.x = (int)pos.x;
	rect.y = (int)pos.y;
	rect.w = width;
	rect.h = height;
}


void Paddle::Update() {
	// Move the paddle
	pos.y = pos.y + speed * dir;

	// Keep paddle in bounds
	if (pos.y < 0) {
		pos.y = 0;
	}
	else if (pos.y + height > SCREEN_HEIGHT) {
		pos.y = SCREEN_HEIGHT - height;
	}

	rect.y = pos.y;
}

void Paddle::SetDir(int d) {
	dir = d;
}

int Paddle::GetId() {
	return id;
}

Vec2 Paddle::GetPos() {
	return pos;
}

SDL_Rect* Paddle::GetRect() {
	return &rect;
}
