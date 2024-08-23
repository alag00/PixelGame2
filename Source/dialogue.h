#pragma once

#include "raylib.h"
#include <vector>

struct Speech 
{
	const char* text = nullptr;
	Texture2D speaker{};
	bool leftSide = true;
};

class Dialogue
{
private:
	std::vector<Speech> speechList{};
	bool active = false;
public:
	~Dialogue();
	void QueueDialogue(bool left, Texture2D avatar, const char* newText);
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