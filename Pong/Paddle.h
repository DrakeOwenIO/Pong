#pragma once

#include "Utils.h"

class Paddle
{
public:
	Paddle(int i);
	void Update();
	void SetDir(int d);
	int GetId();
	
	Vec2 GetPos();
	SDL_Rect* GetRect();

private:
	int id;
	int dir = 0;
	int width = 20;
	int height = 140;
	float speed;

	Vec2 pos;
	SDL_Rect rect;
};

