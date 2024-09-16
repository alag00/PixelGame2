#pragma once

#include "raylib.h"
#include <vector>
#include "text_render.h"
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
	bool active = false;
	TextRenderer txtRend;
public:
	~Dialogue();
	void QueueDialogue(Texture2D leftPort, Texture2D rightPort, const char* newText, bool speakerLeft, Color col);
	void SetActive(bool newValue);
	bool GetActive() { return active; }
	/*
	void SetText(char* newText);
	void SetAvatar(Texture2D avatar);
	void SetSide(bool left);
	*/

	void Update();
	void Render();
};