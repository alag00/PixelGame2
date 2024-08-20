#pragma once
#include "raylib.h"
class MainMenu
{
private:
	int width = 0;
	int height = 0;
	Texture2D bg{};
public:
	void Setup(int w, int h);

	bool Update();
	void Render();
	void Unload();
};