#pragma once
#include "MyFramework.h"
#include "PosObj.h"

class Brick : public PosObj
{
public:
	Brick(){}
	Brick(int nPosX, int nPosY, Sprite* nSprite)
	{
		posX = nPosX;
		posY = nPosY;
		sprite = nSprite;
	}

	bool destroyed = false;
	Sprite* sprite;
};

