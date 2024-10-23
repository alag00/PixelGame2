#pragma once
#include "raylib.h"
#include <string>

class TextRenderer
{
private:
	int frontOffset = 3;
public:
	void RenderText(const char* text, int x, int y, int size, Color front, Color back);
	void RenderText(std::string text, int x, int y, int size, Color front, Color back);
};
