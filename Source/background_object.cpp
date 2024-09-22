#include "background_object.h"

BackgroundObject::~BackgroundObject()
{

}

void BackgroundObject::Setup(Vector2 newPos)
{
	pos = newPos;
	pos.y -= ((float)txr.height / PIXELS_PER_TILE) - OFFSET_Y;

	pos.x -= ((float)txr.width / HALF_OF_TILE) - OFFSET_X;

	size.x = (float)txr.width * PIXEL_SCALE;
	size.y = (float)txr.height * PIXEL_SCALE;
}

void BackgroundObject::SetTextue(Texture2D newTxr)
{
	txr = newTxr;
}

void BackgroundObject::Render()
{
	Rectangle src {0.f,0.f, (float)txr.width, (float)txr.height};
	Rectangle dst{pos.x * config.tileSize, pos.y * config.tileSize, size.x, size.y};
	Vector2 origin{0.f,0.f};
	DrawTexturePro(txr, src, dst, origin, 0.f, WHITE);
}
