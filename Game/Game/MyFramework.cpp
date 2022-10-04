#include "MyFramework.h"
#include <stdio.h>

unsigned int deltaTicks = 0;
unsigned int lastTicks = 0;
Sprite* s;

void calculateDeltaTicks()
{
	int ticks = getTickCount();
	deltaTicks = ticks - lastTicks;
	lastTicks = ticks;
	printf("\n");
	printf("%d", deltaTicks);
}

MyFramework::MyFramework(char* argv[])
{
	printf("test");
	printf("\n");
}

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	width = 1920;
	height = 1080;
	fullscreen = false;
}

bool MyFramework::Init() {
	s = createSprite("data/01-Breakout-Tiles.png");
	int w;
	int h;
	getSpriteSize(s, w, h);
	

	return true;
}

void MyFramework::Close() {

}

bool MyFramework::Tick() {
	drawTestBackground();
	calculateDeltaTicks();
	drawSprite(s, lastTicks, lastTicks);
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