#include "credits.h"

Credits::Credits()
{
	titleList.push_back("Made by");
	titleList.push_back("Software for Code");
	titleList.push_back("Software for Art");
	titleList.push_back("Software for Audio");
	titleList.push_back("Graphical Rendering");
	titleList.push_back(" ");

	textList.push_back("Alag");
	textList.push_back("Visual Studio");
	textList.push_back("Aseprite");
	textList.push_back("Fl Studio");
	textList.push_back("Raylib");
	textList.push_back("Thank you for Playing!");

	pos.x = (float)GetScreenWidth() / 2.f;
	pos.y = 300.f;
}

bool Credits::Update(float dt)
{
	if (fadeTimer > 0.f)
	{
		fadeTimer -= dt;
		if (isFadingIn)
		{
			FRONT_COLOR.a = (char)std::lerp(255, 0, fadeTimer);
			BACK_COLOR.a = (char)std::lerp(255, 0, fadeTimer);
			if (fadeTimer <= 0.f)
			{
				FRONT_COLOR.a = 255;
				BACK_COLOR.a = 255;
			}
		}
		else
		{
			FRONT_COLOR.a = (char)std::lerp(0, 255, fadeTimer);
			BACK_COLOR.a = (char)std::lerp(0, 255, fadeTimer);
			if (fadeTimer <= 0.f)
			{
				isFadingIn = true;
				fadeTimer = FADE_TIME;
				FRONT_COLOR.a = 0;
				BACK_COLOR.a = 0;
				titleList.erase(titleList.begin());
				textList.erase(textList.begin());
			}
		}
		return false;
	}
	lineTimer -= dt;
	if (lineTimer <= 0.f)
	{
		if (titleList.empty() || textList.empty())
		{
			return true;
		}
		isFadingIn = false;
		fadeTimer = FADE_TIME;
		lineTimer = TIME_PER_LINE;
	
	}
	return false;
}

void Credits::Render()
{
	if (titleList.empty() || textList.empty())
	{
		return;
	}
	txtRend.RenderText(titleList.front(), (int)pos.x, (int)pos.y, TITLE_SIZE, FRONT_COLOR, BACK_COLOR);
	txtRend.RenderText(textList.front(), (int)pos.x, (int)pos.y + SPACE, TEXT_SIZE, FRONT_COLOR, BACK_COLOR);

}
