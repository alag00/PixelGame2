#pragma once

#include "raylib.h"
#include <vector>
#include "text_render.h"
#include <string>

struct Speech 
{
	const char* text = nullptr;
	Texture2D lPort{};
	Texture2D rPort{};
	bool speakerLeft;
	Color textCol = WHITE;
};

class Dialogue
{
private:
	std::vector<Speech> speechList{};
	std::string currentChars = "";
	int currentCharsNum = 0;

	const float TIME_BETWEEN_LETTERS = 0.03f;
	float letterTimer = TIME_BETWEEN_LETTERS;

	bool active = false;
	TextRenderer txtRend;
	const float TEXT_BOX_HEIGHT = 200.f;
	const int FONT_SIZE = 30;
	const float NON_SPEAKER_OFFSET = 30.f;
	const float SCALE = 4.f;
public:
	~Dialogue();
	void QueueDialogue(Texture2D leftPort, Texture2D rightPort, const char* newText, bool speakerLeft, Color col);
	void SetActive(bool newValue);
	bool GetActive() { return active; }
	

	void Update(float dt);
	void Render();
};