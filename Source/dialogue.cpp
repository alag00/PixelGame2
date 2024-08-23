#include "dialogue.h"

Dialogue::~Dialogue()
{
}

void Dialogue::QueueDialogue(bool left, Texture2D avatar, const char* newText)
{
	Speech newSpeech = { newText, avatar, left };
	speechList.push_back(newSpeech);
}

void Dialogue::SetActive(bool newValue)
{
	active = newValue;
}
/*
void Dialogue::SetText(char* newText)
{
	text = newText;
}

void Dialogue::SetAvatar(Texture2D avatar)
{
	speaker = avatar;
}

void Dialogue::SetSide(bool left)
{
	leftSide = left;
}
*/
void Dialogue::Update()
{
	if (!active)
	{
		return;
	}
	
	if (IsKeyPressed(KEY_SPACE))
	{
		//UnloadTexture(speechList.front().speaker);
		speechList.erase(speechList.begin());
		if (speechList.empty())
		{
			active = false;
			return;
		}
	}
}

void Dialogue::Render()
{
	if (!active)
	{
		return;
	}
	// Render Box
	Rectangle textBox = { (float)GetScreenWidth() / 2.f, (float)GetScreenHeight(), (float)GetScreenWidth() / 2.f, 200.f };
	textBox.x -= textBox.width / 2.f;
	textBox.y -= textBox.height;
	DrawRectangleRec(textBox, BROWN);
	//DrawRectangle(0, 0, 200, 100, BROWN);
	if (speechList.front().leftSide)
	{
		// place speaker portrait
		//DrawRectangle(50,0,50,50, YELLOW);
		float size = textBox.width / 2.f;
		Rectangle src = {0.f,0.f, (float)speechList.front().speaker.width, (float)speechList.front().speaker.height};
		Rectangle dst = {0.f, (float)GetScreenHeight() - size, size, size };
		DrawRectangleRec(dst, DARKBROWN);
		Vector2 origin = {0.f,0.f};
		DrawTexturePro(speechList.front().speaker, src, dst, origin, 0.f, WHITE);
	}
	else
	{
		float size = textBox.width / 2.f;
		// place speaker portrait
		Rectangle src = { 0.f,0.f, (float)speechList.front().speaker.width, (float)speechList.front().speaker.height };
		src.width = -src.width;
		Rectangle dst = { textBox.x + textBox.width, (float)GetScreenHeight() - size, size, size };
		DrawRectangleRec(dst, DARKBROWN);
		Vector2 origin = { 0.f,0.f };
		DrawTexturePro(speechList.front().speaker, src, dst, origin, 0.f, DARKPURPLE);
	}
	DrawText(speechList.front().text, (int)textBox.x + 10, (int)textBox.y + 10, 30, YELLOW);
}
