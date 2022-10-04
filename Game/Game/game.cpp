
#include <stdio.h>
#include "Framework.h"
#include <iostream>
#define FRAMEWORK_API

/* Test Framework realization */
class MyFramework : public Framework {



public:
	Sprite* s;

	MyFramework(char* argv[])
	{
		printf("test");
		printf("\n");
	}

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 1920;
		height = 1080;
		fullscreen = false;
	}

	virtual bool Init() {
		s = createSprite("data/01-Breakout-Tiles.png");
		setSpriteSize(s, 50, 100);
		int w;
		int h;
		getSpriteSize(s, w, h);
		printf("\n");
		printf("%d %d", w, h);

		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {
		drawTestBackground();
		showCursor(false);
		//printf("\n");
		//printf("% d", getTickCount());
		drawSprite(s, 0, 0);
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

	}

	virtual void onKeyPressed(FRKey k) {
		if (k == FRKey::RIGHT)
		{

		}
	}

	virtual void onKeyReleased(FRKey k) {
	}

	virtual const char* GetTitle() override
	{
		return "Arcanoid";
	}
};

int main(int argc, char* argv[])
{
	return run(new MyFramework(argv));
}


