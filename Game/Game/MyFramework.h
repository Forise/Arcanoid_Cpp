#pragma once
#include "Framework.h"

class MyFramework : public Framework {
public:
	MyFramework(char* argv[]);

	void PreInit(int& width, int& height, bool& fullscreen);
	bool Init();

	void Close();

	bool Tick();

	void onMouseMove(int x, int y, int xrelative, int yrelative);

	void onMouseButtonClick(FRMouseButton button, bool isReleased);

	void onKeyPressed(FRKey k);

	void onKeyReleased(FRKey k);

	unsigned int GetDeltaTicks();

	const char* GetTitle();
};