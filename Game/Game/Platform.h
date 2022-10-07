#pragma once
#include "MyFramework.h"
#include "GameObj.h"

class Platform : public GameObj
{
	const char* platformSpritePath0 = "data/50-Breakout-Tiles.png";
	const char* platformSpritePath1 = "data/51-Breakout-Tiles.png";
	const char* platformSpritePath2 = "data/52-Breakout-Tiles.png";
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

		posX = nPosX;
		posY = nPosY;
		
		centerPosX = posX + (w * 0.5);
		centerPosY = posY - (h * 0.5);
		SetBounds();
	}

	Sprite* sprite0;
	Sprite* sprite1;
	Sprite* sprite2;

	void MoveHorisontal(int deltaX)
	{
		posX += deltaX;
		centerPosX += deltaX;

		SetBounds();
	}
};

