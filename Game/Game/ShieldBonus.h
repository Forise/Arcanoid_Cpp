#pragma once
#include "Brick.h"
#include "MyFramework.h"

class ShieldBonus : public GameObj
{
	const char* SHIELD_BONUS_SPRITE = "data/shield_bonus.png";
public:
	ShieldBonus() {}
	ShieldBonus(int nPosX, int nPosY, int nW, int nH)
	{
		posX = nPosX;
		posY = nPosY;
		w = nW;
		h = nH;
		sprite = createSprite(SHIELD_BONUS_SPRITE);
		dir[0] = 0;
		dir[1] = 1;
		speed = 0.5f;
		setSpriteSize(sprite, w, h);
		SetPos(nPosX, nPosY);
	}

	Sprite* sprite;
};

