#pragma once
#include "MyFramework.h"
#include "GameObj.h"

class Brick : public GameObj
{
public:
	Brick(){}
	Brick(int nPosX, int nPosY, Sprite* nSprite, int nW, int nH)
	{
		posX = nPosX;
		posY = nPosY;
		sprite = nSprite;
		w = nW;
		h = nH;
		centerPosX = posX + (w * 0.5f);
		centerPosY = posY + (h * 0.5f);
		destroyed = false;
		SetPos(nPosX, nPosY);
	}

	bool falling = false;
	bool destroyed = false;
	Sprite* sprite;
};

