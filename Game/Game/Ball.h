#pragma once
#include "MyFramework.h"
#include "GameObj.h"
#include "Utils.h"

class Ball : public GameObj
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

	float dir[2] = {0,0};

	
	Sprite* sprite0;

	void Move(int deltaX, int deltaY)
	{
		posX += deltaX;
		posY += deltaY;
		centerPosX += deltaX;
		centerPosY += deltaY;

		SetBounds();
	}

	void MoveToDir()
	{
		posX += dir[0];
		posY += dir[1];
		centerPosX += dir[0];
		centerPosY += dir[1];

		SetBounds();
	}

	void SetPos(int nX, int nY)
	{
		posX = nX;
		posY = nY;
		centerPosX = posX + (w * 0.5);
		centerPosY = posY - (h * 0.5);

		SetBounds();
	}

	void Bounce(const float* normal)
	{
		float dot = Utils::dotProduct(dir, normal);
		float dot2 = dot * 2;
		dir[0] -= dot2 * *(normal + 0);
		dir[1] -= dot2 * *(normal + 1);
	}
};

