#include "pause_menu.h"

void Slider::Setup(const char* newText, Vector2 pos, Vector2 size)
{
	text = newText;

	backgroundBar.x = pos.x;
	backgroundBar.y = pos.y;
	backgroundBar.width = size.x;
	backgroundBar.height = size.y;

	filledBar = backgroundBar;

	activateBox = backgroundBar;
	float offset = 20.f;
	activateBox.x -= offset;
	activateBox.y -= offset;
	activateBox.width += offset * 2.f;
	activateBox.height += offset * 2.f;
}

bool Slider::Update()
{

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		if (CheckCollisionPointRec(GetMousePosition(), activateBox))
		{
			filledBar.width = GetMousePosition().x - filledBar.x;
			if (filledBar.width < 0.f)
			{
				filledBar.width = 0;
			}
			if (filledBar.width > backgroundBar.width)
			{
				filledBar.width = backgroundBar.width;
			}
			value = filledBar.width / backgroundBar.width;
			return true;
		}
	}
	return false;
}

void Slider::Render()
{
	DrawText(text, (int)filledBar.x, (int)filledBar.y - textSize * 2, textSize, WHITE);
	DrawRectangleRec(backgroundBar, WHITE);
	DrawRectangleRec(filledBar, RED);
	DrawCircle((int)(filledBar.x + filledBar.width), (int)(filledBar.y + (filledBar.height / 2.f)), 10.f, PINK);


	//Color col = YELLOW;
	//col.a = 50;
	//DrawRectangleRec(activateBox, col);
}

float Slider::GetValue()
{
	return value;
}


void Button::Setup(const char* newText, Vector2 pos, Vector2 size, bool isTextButton)
{
	text = newText;
	box.x = pos.x;
	box.y = pos.y;
	box.width = size.x;
	box.height = size.y;

	textButton = isTextButton;
}

bool Button::Update()
{
	isHover = false;
	if (CheckCollisionPointRec(GetMousePosition(), box))
	{
		isHover = true;
	}
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER))
	{
		return isHover;
	}
	return false;
}

void Button::Render()
{
	//Color debugCol = ORANGE;
	//debugCol.a = 50;
	//DrawRectangleRec(box, debugCol);

	Color color = (isHover) ? YELLOW : WHITE;
	if (textButton)
	{
		DrawText(text, (int)box.x + 10, (int)box.y + 10, textSize, color);
	}
	else
	{
		DrawRectangleRec(box, color);
		DrawText(text, (int)box.x , (int)box.y + 10, textSize / 4, BLACK);
	}
}

void PauseMenu::Setup(bool& running, bool& paused)
{
	runningRef = &running;
	pausedRef = &paused;

	int width = GetScreenWidth();
	int height = GetScreenHeight();

	
	float xPos = ((float)width / 2.f) - (resumeSize.x / 2.f);


	resumeButton.Setup("Resume", Vector2(xPos, (float)height / 2.f), resumeSize, true);
	quitButton.Setup("Quit", Vector2(xPos, (float)height - (quitSize.y * 2.f)), quitSize, true);
	audioSlider.Setup("Master Audio", Vector2(width * 0.75f, (float)height / 2.f), sliderSize);
	sfxButton.Setup("Test", Vector2(width * 0.9f, ((float)height / 2.f) - (sfxSize.y / 2.f)), sfxSize, false);

	testSound = LoadSound("Assets/Audio/SFX/Checkpoint.mp3");
	testMusic = LoadMusicStream("Assets/Audio/Music/OminousSpook.mp3");
	PlayMusicStream(testMusic);
}



void PauseMenu::Update()
{
	UpdateMusicStream(testMusic);
	if (audioSlider.Update())
	{
		SetMasterVolume(audioSlider.GetValue());
	}
	if (sfxButton.Update())
	{
		PlaySound(testSound);
	}
	if (resumeButton.Update())
	{
		// resume Game
		*pausedRef = false;
	}
	if (quitButton.Update())
	{
		// Quit Game
		*runningRef = false;
	}
	Render();
}

void PauseMenu::Render()
{
	BeginDrawing();
	ClearBackground(BLACK);
	//DrawRectangleRec(background, BLACK);
	audioSlider.Render();
	sfxButton.Render();
	resumeButton.Render();
	quitButton.Render();
	EndDrawing();
}

