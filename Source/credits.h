#pragma once

#include "text_render.h"
#include <vector>
#include <string>
#include <cmath>

class Credits
{
private:
	//std::string currentTitle{};
	//std::string currentText{};
	std::vector<std::string> titleList{};
	std::vector<std::string> textList{};
	TextRenderer txtRend;
	Vector2 pos{ 0.f,0.f };

	const float TIME_PER_LINE = 3.f;
	float lineTimer = TIME_PER_LINE;
	const float FADE_TIME = 1.f;
	float fadeTimer = FADE_TIME;
	bool isFadingIn = true;

	const int SPACE = 50;
	const int TITLE_SIZE = 30;
	const int TEXT_SIZE = 50;
	Color FRONT_COLOR = WHITE;
	Color BACK_COLOR = BLACK;
public:
	Credits();
	bool Update(float dt);
	void Render();
};