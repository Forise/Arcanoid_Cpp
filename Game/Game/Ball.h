#pragma once
#include "MyFramework.h"

class Ball
{
	const char* ballSpritePath0 = "data/ball.png";
public:
	Ball() {
	}

	Ball(int nPosX, int nPosY, int nW, int nH)
	{
		w = nW;
		h = nH;

		sprite0 = createSprite(ballSpritePath0);
		setSpriteSize(sprite0, w, h);

		posX = nPosX;
		posY = nPosY;

		centerPosX = posX + (w * 0.5);
		centerPosY = posY - (h * 0.5);
	}
	int posX = 0;
	int posY = 0;

	int dir[2] = {0,0};

	int h;
	int w;

	int centerPosX = 0;
	int centerPosY = 0;
	Sprite* sprite0;

	void Move(int deltaX, int deltaY)
	{
		posX += deltaX;
		posY += deltaY;
		centerPosX += deltaX;
		centerPosY += deltaY;
	}
};

