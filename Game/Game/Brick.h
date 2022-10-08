#pragma once
#include "MyFramework.h"
#include "GameObj.h"
#include "ShieldBonus.h"
#include "Utils.h"

class Brick : public GameObj
{
private :
	int spawnProbability = 15;
public:
	Brick(){}
	Brick(int nPosX, int nPosY, Sprite* nSprite, int nW, int nH)
	{
		posX = nPosX;
		posY = nPosY;
		w = nW;
		h = nH;
		destroyed = false;
		sprite = nSprite;
		SetPos(nPosX, nPosY);
	}
	Sprite* sprite;
	bool destroyed = false;

	virtual void Destroy()
	{
		destroyed = true;
		
		SetPos(-1000, -1000);
	}

	bool TrySpawn()
	{
		int rnd = Utils::getRandom(0, 100);//rand() % 100 + 1;
		if (rnd <= spawnProbability)
		{
			return true;
		}
		return false;
	}
};

