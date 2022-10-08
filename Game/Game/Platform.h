#pragma once
#include "MyFramework.h"
#include "GameObj.h"

class Platform : public GameObj
{
	const char* platformSpritePath0 = "data/platform_3.png";
	const char* platformSpritePath1 = "data/platform_2.png";
	const char* platformSpritePath2 = "data/platform_1.png";
public:
	Platform(){
	}

	Platform(int nPosX, int nPosY, int nW, int nH)
	{
		w = nW;
		h = nH;

		sprite0 = createSprite(platformSpritePath0);
		sprite1 = createSprite(platformSpritePath1);
		sprite2 = createSprite(platformSpritePath2);
		setSpriteSize(sprite0, w, h);
		setSpriteSize(sprite1, w, h);
		setSpriteSize(sprite2, w, h);

		SetPos(nPosX, nPosY);
		hp = 3;
	}

	Sprite* sprite0;
	Sprite* sprite1;
	Sprite* sprite2;
	int hp;

	Sprite* GetSprite()
	{
		switch (hp)
		{
			case 3:
				return sprite0;
				break;
			case 2:
				return sprite1;
				break;
			case 1:
				return sprite2;
				break;
			default:
				return sprite0;
				break;
		}
	}

	void MoveHorisontal(int deltaX)
	{
		posX += deltaX;
		centerPosX += deltaX;

		SetBounds();
	}
	
	int GetDamage()
	{
		hp--;
		return hp;
	}
	
	int GetDamage(int damage)
	{
		hp-= damage;
		return hp;
	}
};

