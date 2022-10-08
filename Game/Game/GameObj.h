#pragma once
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

	float dir[2] = { 0,0 };

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
		centerPosY = posY - (h * 0.5);

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
		posX += dir[0] * speed;
		posY += dir[1] * speed;
		centerPosX += dir[0] * speed;
		centerPosY += dir[1] * speed;

		SetBounds();
	}

	bool CollidesWithTopEdge(float* pos, float weight, float height)
	{
		return ((pos[0] >= posX && pos[0] <= posX + w) ||
			(pos[0] + weight >= posX && pos[0] <= posX + w)) &&
			pos[1] + height >= posY;
	}
	
	bool CollidesWithTopEdge(GameObj* go)
	{
		return ((go->posX >= posX && go->posX <= posX + w) ||
			(go->posX + go->w >= posX && go->posX <= posX + w)) &&
			go->posY + go->h >= posY;
	}
	
	bool CollidesWithBottomEdge(GameObj* go)
	{
		return ((go->posX >= posX && go->posX <= posX + w) ||
			(go->posX + go->w >= posX && go->posX <= posX + w)) &&
			(go->posY - (posY + h) <= 0 && posY < go->posY);
	}
};

