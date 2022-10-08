#pragma once
#include "GameObj.h"
#include "MyFramework.h"

class ShieldObj : public GameObj
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
		sprite = nSprite;
		SetPos(nPosX, nPosY);
	}

	Sprite* sprite;
};

