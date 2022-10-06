#include "MyFramework.h"
#include <stdio.h>
#include "Brick.h"
#include "Platform.h"
#include "Ball.h"

#pragma region GameState
enum class GameState
{
	Init = 0,
	Playing = 1,
	End = 2,
};
#pragma endregion GameState

GameState gs = GameState::Init;

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

const int brickMapW = 11;
const int brickMapH = 6;
Brick brickMap[brickMapH][brickMapW];

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
Platform platform;

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
	if (movingRight && platform.posX + platform.w < mWidth)
	{
		platform.MoveHorisontal(deltaTicks);
	}
	else if (movingLeft && platform.posX > 0)
	{
		platform.MoveHorisontal(deltaTicks * -1);
	}
}
#pragma endregion Platform

#pragma region Ball
Ball ball;

void createBall()
{
	int bW = platform.w / 10;
	int bH = bW;
	ball = Ball(platform.centerPosX - bW / 2, platform.centerPosY, bW, bH);
}

void tryMoveBall()
{

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
	return true;
}

void MyFramework::Close() {

}

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

	switch (gs)
	{
	case GameState::Init:
		break;
	case GameState::Playing:
		break;
	case GameState::End:
		break;
	default:
		break;
	}	

	
	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {

	/*printf("\n");
	printf("mouse pos %d, %d", x, y);
	printf("\n");
	printf("relative mouse pos %d, %d", xrelative, yrelative);
	printf("\n");*/
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {
	
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