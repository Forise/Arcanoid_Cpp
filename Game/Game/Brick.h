#pragma once
#include "MyFramework.h"
#include "GameObj.h"

class Brick : public GameObj
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

