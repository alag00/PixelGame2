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

void Dialogue::Update(float dt)
{
	if (!active)
	{
		return;
	}

	letterTimer -= dt;
	if (letterTimer <= 0.f)
	{
		letterTimer = TIME_BETWEEN_LETTERS;
		currentCharsNum++;
		if (currentCharsNum > strlen(speechList.front().text))
		{
			currentCharsNum = (int)strlen(speechList.front().text);
		}
		
		currentChars = "";

		for (int i = 0; i < currentCharsNum; i++)
		{
			currentChars += speechList.front().text[i];
		}
		
	}
	
	
	if (IsKeyPressed(KEY_SPACE))
	{
		if (currentCharsNum == strlen(speechList.front().text))
		{

			currentCharsNum = 0;
			currentChars = "";
			speechList.erase(speechList.begin());
			if (speechList.empty())
			{
				active = false;
				return;
			}
		}
		else
		{
			currentChars = speechList.front().text;
			currentCharsNum = (int)strlen(speechList.front().text);
		}
	}
}

void Dialogue::Render()
{
	if (!active)
	{
		return;
	}
	
	Rectangle textBox = { (float)GetScreenWidth() / 2.f, (float)GetScreenHeight(), (float)GetScreenWidth() / 2.f, TEXT_BOX_HEIGHT };
	textBox.x -= textBox.width / 2.f;
	textBox.y -= textBox.height;
	DrawRectangleRec(textBox, DARKBROWN);

	int margin = 8;
	DrawRectangle((int)textBox.x + margin, (int)textBox.y + margin, (int)textBox.width - margin * 2, (int)textBox.height - margin * 2, BROWN);

	
	Color nonSpeakColor = DARKGRAY;
	Rectangle src = { 0.f,0.f, (float)speechList.front().rPort.width, (float)speechList.front().rPort.height };
	Vector2 origin = { 0.f,0.f };

	float width = src.width * SCALE;
	float height = src.height * SCALE;

	Rectangle dst = { textBox.x - width, (float)GetScreenHeight() - height, width, height };
	if (!speechList.front().speakerLeft)
	{
		dst.y += NON_SPEAKER_OFFSET;
	
		DrawTexturePro(speechList.front().lPort, src, dst, origin, 0.f, nonSpeakColor);
	}
	else
	{
		
		DrawTexturePro(speechList.front().lPort, src, dst, origin, 0.f, WHITE);
	}
	dst = { textBox.x + textBox.width, (float)GetScreenHeight() - height, width, height };

	if (speechList.front().speakerLeft)
	{
		dst.y += NON_SPEAKER_OFFSET;
		
		DrawTexturePro(speechList.front().rPort, src, dst, origin, 0.f, nonSpeakColor);
	}
	else
	{
		
		DrawTexturePro(speechList.front().rPort, src, dst, origin, 0.f, WHITE);
	}
	
	txtRend.RenderText(currentChars, (int)textBox.x + FONT_SIZE, (int)textBox.y + FONT_SIZE, FONT_SIZE, speechList.front().textCol, BLACK);
	
}
