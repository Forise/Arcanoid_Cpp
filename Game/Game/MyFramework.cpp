#include "MyFramework.h"
#include <stdio.h>
#include "Brick.h"
#include "Platform.h"
#include "Ball.h"
#include <math.h>
#include "Utils.h"

#pragma region GameState
enum class GameState
{
	Init = 0,
	Playing = 1,
	End = 2,
};
#pragma endregion GameState

GameState gs = GameState::Init;
const int brickMapW = 11;
const int brickMapH = 6;

const float NORMAL_LEFT[2] = { -1, 0 };
const float NORMAL_RIGHT[2] = { 1, 0 };
const float NORMAL_DOWN[2] = { 0, 1 };
const float NORMAL_UP[2] = { 0, -1 };
Brick brickMap[brickMapH][brickMapW];
Ball ball;
Platform platform;


#pragma region DeltaTicks
unsigned int deltaTicks = 0;
unsigned int lastTicks = 0;

void calculateDeltaTicks()
{
	int ticks = getTickCount();
	deltaTicks = ticks - lastTicks;
	lastTicks = ticks;
	/*printf("\n");
	printf("%d", deltaTicks);*/
}
#pragma endregion DeltaTicks

#pragma region Map
int mWidth;
int mHeight;

Brick createBrick(int posX, int posY, const char* spritePath, int width = 0, int height = 0)
{
	Sprite* s = createSprite(spritePath);
	setSpriteSize(s, width, height);
	Brick b = Brick(posX, posY, s);
	b.centerPosX = posX + (width * 0.5f);
	b.centerPosY = posY + (height * 0.5f);
	return b;
}

void fillBrickMap()
{
	int brickW = mWidth / brickMapW;
	int brickH = brickW / 3;

	int wOffset = 0;
	int hOffset = 0;

	for (int i = 0; i < brickMapH; i++)
	{
		for (int k = 0; k < brickMapW; k++)
		{
			brickMap[i][k] = createBrick(wOffset, hOffset, "data/12.png", brickW, brickH);
			wOffset += brickW;
		}
		wOffset = 0;
		hOffset += brickH;
	}
}

void drawBrickMap()
{
	for (int i = 0; i < brickMapH; i++)
	{
		for (int k = 0; k < brickMapW; k++)
		{
			if (brickMap[i][k].destroyed == false)
			{
				drawSprite(brickMap[i][k].sprite, brickMap[i][k].posX, brickMap[i][k].posY);
			}
		}
	}
}
#pragma endregion Map

#pragma region Platform
bool movingLeft = false;
bool movingRight = false;

void createPlatform()
{
	int pW = mWidth / brickMapW * 2;
	int pH = pW / 4;
	platform = Platform((mWidth * 0.5f) - (pW * 0.5f), mHeight - pH, pW, pH);
}

void tryMovePlatform()
{
	int xVel = 0;

	if (movingRight && platform.posX + platform.w < mWidth)
	{
		xVel = deltaTicks;
		platform.MoveHorisontal(xVel);
	}
	else if (movingLeft && platform.posX > 0)
	{
		xVel = deltaTicks * -1;
		platform.MoveHorisontal(xVel);
	}
}
#pragma endregion Platform

#pragma region Ball

void createBall()
{
	int bW = platform.w / 10;
	int bH = bW;
	ball = Ball(platform.centerPosX - bW / 2, platform.centerPosY, bW, bH);
}

void tryMoveBall()
{
	int bW = platform.w / 10;
	int bH = bW;
	switch (gs)
	{
		case GameState::Init:
			ball.SetPos(platform.centerPosX - bW / 2, platform.centerPosY);
			break;
		case GameState::Playing:
			ball.MoveToDir();
			break;
		case GameState::End:
			break;
		default:
			break;
	}
}
#pragma endregion Ball


#pragma region MyFramework
MyFramework::MyFramework(char* argv[])
{
	printf("test");
	printf("\n");
}

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	width = 800;
	height = 640;
	mWidth = width;
	mHeight = height;
	fullscreen = false;
}

bool MyFramework::Init() {
	fillBrickMap();
	createPlatform();
	createBall();
	showCursor(true);
	return true;
}

void MyFramework::Close() {

}
bool bounced = false;
bool MyFramework::Tick() {
	calculateDeltaTicks();

	drawTestBackground();
	Sprite* back = createSprite("data/17.png");
	setSpriteSize(back, mWidth, mHeight);
	drawSprite(back, 0, 0);
	drawBrickMap();
	drawSprite(platform.sprite0, platform.posX, platform.posY);
	drawSprite(ball.sprite0, ball.posX, ball.posY);
	tryMovePlatform();
	tryMoveBall();

	switch (gs)
	{
	case GameState::Init:
		break;
	case GameState::Playing:
		/*if (lastTicks > 3000 && bounced == false)
		{
			ball.Bounce(NORMAL_LEFT);
			bounced = true;
		}*/
		break;
	case GameState::End:
		break;
	default:
		break;
	}	

	
	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
	if (gs == GameState::Init)
	{
		ball.dir[0] = x - ball.posX;
		ball.dir[1] = y - ball.posY;

		Utils::normalize(ball.dir);

		/*float mag = sqrt((ball.dir[0] * ball.dir[0]) + (ball.dir[1] * ball.dir[1]));
		if (mag < 0)
		{
			mag = mag * -1;
		}

		ball.dir[0] /= mag;
		ball.dir[1] /= mag;*/
		/*printf("ball dir x = %d\n", ball.dir[0]);
		printf("ball dir y = %d\n", ball.dir[1]);*/
	}
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {
	if (gs == GameState::Init)
	{
		gs = GameState::Playing;
		showCursor(false);
	}
}

void MyFramework::onKeyPressed(FRKey k) {
	if (k == FRKey::RIGHT)
	{
		movingLeft = false;
		movingRight = true;
	}
	else if (k == FRKey::LEFT)
	{
		movingLeft = true;
		movingRight = false;
		platform.MoveHorisontal(deltaTicks * -1);
	}
}

void MyFramework::onKeyReleased(FRKey k) {
	if (k == FRKey::RIGHT)
	{
		movingRight = false;
	}
	else if (k == FRKey::LEFT)
	{
		movingLeft = false;
	}
}

unsigned int MyFramework::GetDeltaTicks()
{
	return deltaTicks;
}

const char* MyFramework::GetTitle()
{
	return "Arcanoid";
}
#pragma endregion MyFramework