#pragma once
#include "MyFramework.h"
#include "GameObj.h"
#include "Utils.h"

class Ball : public GameObj
{
	const char* ballSpritePath0 = "data/ball.png";
public:
	Ball() {
	}

	Ball(int nPosX, int nPosY, int nW, int nH)
	{
		w = nW;
		h = nH;

		sprite0 = createSprite(ballSpritePath0);
		setSpriteSize(sprite0, w, h);
		speed = 2;
		SetPos(nPosX, nPosY);
	}

	
	Sprite* sprite0;

	void Bounce(const float* normal)
	{
		float dot = Utils::dotProduct(dir, normal);
		float dot2 = dot * 2;
		dir[0] -= dot2 * *(normal + 0);
		dir[1] -= dot2 * *(normal + 1);
	}
};

