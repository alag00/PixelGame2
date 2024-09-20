#pragma once
#include "raylib.h"
#include <cstring>

class TextRenderer
{
private:
	int frontOffset = 3;
public:
	void RenderText(const char* text, int x, int y, int size, Color front, Color back);
};
