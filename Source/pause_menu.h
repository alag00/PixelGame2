#pragma once
#include "raylib.h"

class Slider
{
private:
	const char* text = nullptr;
	int textSize = 20;
	float value = 0.f;
	Rectangle filledBar{ 0.f,0.f,0.f,0.f };
	Rectangle backgroundBar{ 0.f,0.f,0.f,0.f };
	Rectangle activateBox{ 0.f,0.f,0.f,0.f };

	bool isHover = false;
public:
	void Setup(const char* newText, Vector2 pos, Vector2 size);
	bool Update();
	void Render();
	float GetValue();
};

class Button
{
private:
	bool isHover = false;
	Rectangle box{ 0.f,0.f,0.f,0.f };
	const char* text = nullptr;
	int textSize = 60;
	bool textButton = true;
public:
	void Setup(const char* newText, Vector2 pos, Vector2 size, bool isTextButton);
	bool Update();
	void Render();
};

class PauseMenu
{
private:
	//Rectangle background{ 0.f,0.f,0.f,0.f };

	Music testMusic;
	Sound testSound;

	Slider audioSlider;
	//Slider musicSlider;
	Vector2 sliderSize{ 200.f, 10.f };
	Button sfxButton;
	Vector2 sfxSize{ 40.f,40.f };

	Button resumeButton;
	Button quitButton;

	Vector2 resumeSize{ 250.f,100.f };
	Vector2 quitSize{ 150.f,100.f };

	bool* runningRef = nullptr;
	bool* pausedRef = nullptr;
public:
	void Setup(bool& running, bool& paused);
	
	void Update();
	void Render();
};