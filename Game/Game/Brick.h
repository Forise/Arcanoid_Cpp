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
		destroyed = false;
		SetPos(nPosX, nPosY);
	}

	bool destroyed = false;
	Sprite* sprite;

	void Destroy()
	{
		destroyed = true;
		SetPos(-1000, -1000);
	}
};

