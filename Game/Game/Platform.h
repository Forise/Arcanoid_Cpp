#pragma once
#include "MyFramework.h"
class Platform
{
public:
	Platform(){}
	Platform(int nPosX, int nPosY, Sprite* nSprite0, Sprite* nSprite1, Sprite* nSprite2, int nW, int nH)
	{
		posX = nPosX;
		posY = nPosY;
		sprite0 = nSprite0;
		sprite1 = nSprite1;
		sprite2 = nSprite2;
		w = nW;
		h = nH;
	}
	int posX = 0;
	int posY = 0;

	int h;
	int w;

	int centerPosX = 0;
	int centerPosY = 0;
	Sprite* sprite0;
	Sprite* sprite1;
	Sprite* sprite2;

	void MoveHorisontal(int deltaX)
	{
		posX += deltaX;
		centerPosX += deltaX;
	}
};

