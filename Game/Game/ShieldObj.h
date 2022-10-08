#pragma once
#include "Brick.h"

class ShieldObj : public Brick
{
public:
	ShieldObj(){}
	ShieldObj (int nPosX, int nPosY, Sprite* nSprite, int nW, int nH)
	{
		posX = nPosX;
		posY = nPosY;
		sprite = nSprite;
		w = nW;
		h = nH;
		destroyed = false;
		sprite = nSprite;
		SetPos(nPosX, nPosY);
	}
};

