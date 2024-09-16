#include "background_object.h"

BackgroundObject::~BackgroundObject()
{
	//UnloadTexture(txr);
}

void BackgroundObject::Setup(Vector2 newPos)
{
	pos = newPos;
	pos.y -= ((float)txr.height / 16.f) -1;
	//pos.y -= ((float)txr.height / 24.f);
	pos.x -= ((float)txr.width / 32.f) -0.5f;

	size.x = (float)txr.width * 4.f;
	size.y = (float)txr.height * 4.f;
}

void BackgroundObject::SetTextue(Texture2D newTxr)
{
	txr = newTxr;
}

void BackgroundObject::Render()
{
	Rectangle src {0.f,0.f, (float)txr.width, (float)txr.height};
	Rectangle dst{pos.x * 64.f, pos.y * 64.f, size.x, size.y};
	Vector2 origin{0.f,0.f};
	DrawTexturePro(txr, src, dst, origin, 0.f, WHITE);
}
