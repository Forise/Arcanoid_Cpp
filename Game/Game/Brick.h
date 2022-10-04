#pragma once
#include "MyFramework.h"
class Brick
{
public:
	Brick(){}
	Brick(int nPosX, int nPosY, Sprite* nSprite)
	{
		posX = nPosX;
		posY = nPosY;
		sprite = nSprite;
	}
	int posX = 0;
	int posY = 0;
	
	int centerPosX = 0;
	int centerPosY = 0;
	Sprite* sprite;
};

