#pragma once
#include "enumSide.h"
#include "MyFramework.h"
class GameObj
{
public:
	float posX = 0;
	float posY = 0;
	float centerPosX = 0;
	float centerPosY = 0;
	float speed = 1;

	int h;
	int w;

	float rightCenterBorderPos[2] = { 0,0 };
	float leftCenterBorderPos[2] = { 0,0 };
	float upCenterBorderPos[2] = { 0,0 };
	float downCenterBorderPos[2] = { 0,0 };

#if defined(DEBUG_G)
	Sprite* d_s_0;
	Sprite* d_s_1;
	Sprite* d_s_2;
	Sprite* d_s_3;
#endif
	float dir[2] = { 0,0 };


	GameObj()
	{
#if defined(DEBUG_G)
		d_s_0 = createSprite("data/red_d.png");
		d_s_1 = createSprite("data/yellow_d.png");
		d_s_2 = createSprite("data/green_d.png");
		d_s_3 = createSprite("data/black_d.png"); 
#endif
	}


	void SetBounds()
	{
		rightCenterBorderPos[0] = posX + w;
		rightCenterBorderPos[1] = centerPosY;

		leftCenterBorderPos[0] = posX;
		leftCenterBorderPos[1] = centerPosY;

		upCenterBorderPos[0] = centerPosX;
		upCenterBorderPos[1] = posY;

		downCenterBorderPos[0] = centerPosX;
		downCenterBorderPos[1] = posY + h;
	}

	void SetPos(int nX, int nY)
	{
		posX = nX;
		posY = nY;
		centerPosX = posX + (w * 0.5);
		centerPosY = posY + (h * 0.5);

		SetBounds();
	}

	void Move(float deltaX, float deltaY)
	{
		posX += deltaX;
		posY += deltaY;
		centerPosX += deltaX;
		centerPosY += deltaY;

		SetBounds();
	}

	void MoveToDir()
	{
		Move(dir[0] * speed, dir[1] * speed);
	}

	bool CheckCollideSide(GameObj o, enumSide side)
	{
		switch (side)
		{
			case enumSide::Left:
				return CheckPointInBoundsOfObject(leftCenterBorderPos[0], leftCenterBorderPos[1], o);
				break;
			case enumSide::Right:
				return CheckPointInBoundsOfObject(rightCenterBorderPos[0], rightCenterBorderPos[1], o);
				break;
			case enumSide::Up:
				return CheckPointInBoundsOfObject(upCenterBorderPos[0], upCenterBorderPos[1], o);
				break;
			case enumSide::Down:
				return CheckPointInBoundsOfObject(downCenterBorderPos[0], downCenterBorderPos[1], o);
				break;
		}
		return false;
	}

	bool CheckPointInBoundsOfObject(float px, float py, GameObj o)
	{
		return px >= o.posX && px <= o.posX + o.w &&
			py >= o.posY && py <= o.posY + o.h;
	}
};

