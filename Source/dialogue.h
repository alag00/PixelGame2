#pragma once

#include "raylib.h"
#include <vector>

struct Speech 
{
	const char* text = nullptr;
	Texture2D lPort{};
	Texture2D rPort{};
	//bool leftSide = true;
};

class Dialogue
{
private:
	std::vector<Speech> speechList{};
	bool active = false;
public:
	~Dialogue();
	void QueueDialogue(Texture2D leftPort, Texture2D rightPort, const char* newText);
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