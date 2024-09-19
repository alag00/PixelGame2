#include "dialogue.h"

Dialogue::~Dialogue()
{
	speechList.clear();
}

void Dialogue::QueueDialogue(Texture2D leftPort, Texture2D rightPort, const char* newText, bool speakerLeft, Color col)
{
	Speech newSpeech = { newText, leftPort, rightPort, speakerLeft, col};
	speechList.push_back(newSpeech);
}

void Dialogue::SetActive(bool newValue)
{
	active = newValue;
}

void Dialogue::Update()
{
	if (!active)
	{
		return;
	}
	
	if (IsKeyPressed(KEY_SPACE))
	{
	
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
	
	Rectangle textBox = { (float)GetScreenWidth() / 2.f, (float)GetScreenHeight(), (float)GetScreenWidth() / 2.f, 200.f };
	textBox.x -= textBox.width / 2.f;
	textBox.y -= textBox.height;
	DrawRectangleRec(textBox, DARKBROWN);

	int margin = 8;
	DrawRectangle((int)textBox.x + margin, (int)textBox.y + margin, (int)textBox.width - margin * 2, (int)textBox.height - margin * 2, BROWN);

	
	Color nonSpeakColor = DARKGRAY;
	Rectangle src = { 0.f,0.f, 80.f, 80.f };
	Vector2 origin = { 0.f,0.f };

	float width = (float)speechList.front().rPort.width * 4.f;
	float height = (float)speechList.front().rPort.height * 4.f;

	Rectangle dst = { textBox.x - width, (float)GetScreenHeight() - height, width, height };
	if (!speechList.front().speakerLeft)
	{
		dst.y += 30.f;
	
		DrawTexturePro(speechList.front().lPort, src, dst, origin, 0.f, nonSpeakColor);
	}
	else
	{
		
		DrawTexturePro(speechList.front().lPort, src, dst, origin, 0.f, WHITE);
	}
	dst = { textBox.x + textBox.width, (float)GetScreenHeight() - height, width, height };

	if (speechList.front().speakerLeft)
	{
		dst.y += 30.f;
		
		DrawTexturePro(speechList.front().rPort, src, dst, origin, 0.f, nonSpeakColor);
	}
	else
	{
		
		DrawTexturePro(speechList.front().rPort, src, dst, origin, 0.f, WHITE);
	}
	
	txtRend.RenderText(speechList.front().text, (int)textBox.x + 30, (int)textBox.y + 30, 30, speechList.front().textCol, BLACK);
	
}
