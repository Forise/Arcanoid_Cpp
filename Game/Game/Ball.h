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

		SetPos(nPosX, nPosY);
	}
	float posX = 0;
	float posY = 0;

	float dir[2] = {0,0};

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

	void MoveToDir()
	{
		posX += dir[0];
		posY += dir[1];
		centerPosX += dir[0];
		centerPosY += dir[1];
	}

	void SetPos(int nX, int nY)
	{
		posX = nX;
		posY = nY;
		centerPosX = posX + (w * 0.5);
		centerPosY = posY - (h * 0.5);
	}
};

