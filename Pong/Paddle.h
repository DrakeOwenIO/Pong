#pragma once

#include <SDL_ttf.h>
#include "Utils.h"

class Paddle
{
public:
	Paddle(int i);
	void Update();
	void SetDir(int d);
	void IncScore();
	void showScore(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);

	int GetId();
	Vec2 GetPos();
	SDL_Rect* GetRect();

private:
	int id;
	int dir = 0;
	int width = 20;
	int height = 140;
	float speed;
	int score = 0;

	Vec2 pos;
	SDL_Rect rect;
	SDL_Rect scoreRect;
	SDL_Surface* scoreSurface = nullptr;
	SDL_Texture* scoreTexture = nullptr;
};

