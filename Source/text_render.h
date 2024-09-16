#pragma once
#include "raylib.h"
#include <cstring>

class TextRenderer
{
private:
public:
	void RenderText(const char* text, int x, int y, int size, Color front, Color back)
	{
		DrawText(text, x, y, size, back);
		DrawText(text, x - 3, y - 3, size, front);

	}
};
