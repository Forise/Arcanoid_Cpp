#pragma once
#include "MyFramework.h"
#include "GameObj.h"
class BombObj : public GameObj
{
	const char* BOMB_SPRITE = "data/bomb.png";
public:
	BombObj() {}
	BombObj(int nPosX, int nPosY, int nW, int nH)
	{
		posX = nPosX;
		posY = nPosY;
		w = nW;
		h = nH;
		destroyed = false;
		sprite = createSprite(BOMB_SPRITE);
		setSpriteSize(sprite, w, h);
		dir[0] = 0;
		dir[1] = 1;
		speed = 0.5f;
		SetPos(nPosX, nPosY);
	}
	int damage = 1;
	Sprite* sprite;
	bool destroyed = false;

	virtual void Destroy()
	{
		destroyed = true;

		SetPos(-1000, -1000);
	}
};

