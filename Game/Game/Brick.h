#pragma once
#include "MyFramework.h"
#include "GameObj.h"
#include "ShieldBonus.h"
#include "Utils.h"

class Brick : public GameObj
{
private :
	int spawnShieldProbability = 15;
	int spawnBombProbability = 15;
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

	bool TrySpawnShield()
	{
		int rnd = Utils::getRandom(1, 100);
		if (rnd <= spawnShieldProbability)
		{
			return true;
		}
	}
	
	bool TrySpawnBomb()
	{
		int rnd = Utils::getRandom(1, 100);
		if (rnd <= spawnBombProbability)
		{
			printf("bomb spawn: prob = %d, rnd = %d\n", spawnBombProbability, rnd);
			return true;
		}
	}
};

