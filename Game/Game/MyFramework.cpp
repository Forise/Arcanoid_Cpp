#include "MyFramework.h"
#include <stdio.h>
#include "Brick.h"

unsigned int deltaTicks = 0;
unsigned int lastTicks = 0;

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
	b.centerPosX = posX + (width / 2);
	b.centerPosY = posY + (height / 2);
	return b;
}

void fillBrickMap()
{
	int brickW = mWidth / 11;
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
			drawSprite(brickMap[i][k].sprite, brickMap[i][k].posX, brickMap[i][k].posY);
		}
	}
}

void calculateDeltaTicks()
{
	int ticks = getTickCount();
	deltaTicks = ticks - lastTicks;
	lastTicks = ticks;
	/*printf("\n");
	printf("%d", deltaTicks);*/
}

MyFramework::MyFramework(char* argv[])
{
	printf("test");
	printf("\n");
}

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	width = 1080;
	height = 1080;
	mWidth = width;
	mHeight = height;
	fullscreen = false;
}

bool MyFramework::Init() {
	//s = createSprite("data/01-Breakout-Tiles.png");
	//int w;
	//int h;
	//getSpriteSize(s, w, h);
	//b = createBrick(0, 0, "data/01-Breakout-Tiles.png");
	fillBrickMap();
	return true;
}

void MyFramework::Close() {

}

bool MyFramework::Tick() {
	drawTestBackground();
	calculateDeltaTicks();
	drawBrickMap();
	//drawSprite(b.sprite, 0, 0);
	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {

}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {

}

void MyFramework::onKeyPressed(FRKey k) {
	if (k == FRKey::RIGHT)
	{

	}
}

void MyFramework::onKeyReleased(FRKey k) {
}

unsigned int MyFramework::GetDeltaTicks()
{
	return deltaTicks;
}

const char* MyFramework::GetTitle()
{
	return "Arcanoid";
}