#pragma once
#include <SDL_mixer.h>
#include "Paddle.h"

class Ball
{
public:
	Ball();
	void Update(Paddle* lPaddle, Paddle* rPaddle);
	void HandleCollision(Paddle* paddle);
	bool TopCollision(Paddle* paddle);
	bool BottomCollision(Paddle* paddle);
	void Shutdown();
	void Reset();

	SDL_Rect* GetRect();

private:
	int dir = 0;
	int size = 20;
	float speed;
	const float INITIAL_SPEED = 0.10;
	const int MAX_SPEED = 0.20;

	Vec2 pos;
	Vec2 vel;
	SDL_Rect rect;

	Mix_Chunk* sound = nullptr;
};



