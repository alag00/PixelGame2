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
	DrawRectangleRec(textBox, DARKBROWN);

	int margin = 8;
	DrawRectangle((int)textBox.x + margin, (int)textBox.y + margin, (int)textBox.width - margin * 2, (int)textBox.height - margin * 2, BROWN);

	//DrawRectangle(0, 0, 200, 100, BROWN);
	Color nonSpeakColor = DARKGRAY;
	Rectangle src = { 0.f,0.f, 80.f, 80.f };
	Vector2 origin = { 0.f,0.f };

	float width = (float)speechList.front().rPort.width * 4.f;
	float height = (float)speechList.front().rPort.height * 4.f;

	Rectangle dst = { textBox.x - width, (float)GetScreenHeight() - height, width, height };
	if (!speechList.front().speakerLeft)
	{
		dst.y += 30.f;
		//DrawRectangleRec(dst, DARKBROWN);
		DrawTexturePro(speechList.front().lPort, src, dst, origin, 0.f, nonSpeakColor);
	}
	else
	{
		//DrawRectangleRec(dst, DARKBROWN);
		DrawTexturePro(speechList.front().lPort, src, dst, origin, 0.f, WHITE);
	}
	dst = { textBox.x + textBox.width, (float)GetScreenHeight() - height, width, height };
	//DrawRectangleRec(dst, DARKBROWN);
	if (speechList.front().speakerLeft)
	{
		dst.y += 30.f;
		//DrawRectangleRec(dst, DARKBROWN);
		DrawTexturePro(speechList.front().rPort, src, dst, origin, 0.f, nonSpeakColor);
	}
	else
	{
		//DrawRectangleRec(dst, DARKBROWN);
		DrawTexturePro(speechList.front().rPort, src, dst, origin, 0.f, WHITE);
	}
	/*
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
		//float size = textBox.width / 2.f;
		float width = (float)speechList.front().speaker.width * 3.f;
		float height = (float)speechList.front().speaker.height * 3.f;

		// place speaker portrait
		Rectangle src = { 0.f,0.f, (float)speechList.front().speaker.width, (float)speechList.front().speaker.height };
		//src.width = -src.width;
		Rectangle dst = { textBox.x + textBox.width, (float)GetScreenHeight() - height, width, height };
		DrawRectangleRec(dst, DARKBROWN);
		Vector2 origin = { 0.f,0.f };
		DrawTexturePro(speechList.front().speaker, src, dst, origin, 0.f, WHITE);
	}
	*/
	txtRend.RenderText(speechList.front().text, (int)textBox.x + 30, (int)textBox.y + 30, 30, speechList.front().textCol, BLACK);
	//DrawText(speechList.front().text, (int)textBox.x + 10, (int)textBox.y + 10, 30, WHITE);
	//DrawText(speechList.front().text, (int)textBox.x + 10 + 1, (int)textBox.y + 10 + 1, 30, BLACK);
}
