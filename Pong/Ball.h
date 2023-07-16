#pragma once

#include "Paddle.h"

class Ball
{
public:
	Ball();
	void Update(Paddle* lPaddle, Paddle* rPaddle);
	void SetVel(float x, float y);
	void InvertXVel();
	void HandleCollision(Paddle* paddle);

	SDL_Rect* GetRect();

private:
	int dir = 0;
	int size = 20;
	float speed;

	Vec2 pos;
	Vec2 vel;
	SDL_Rect rect;
};



