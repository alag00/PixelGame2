#include "text_render.h"

void TextRenderer::RenderText(const char* text, int x, int y, int size, Color front, Color back)
{
	DrawText(text, x, y, size, back);
	DrawText(text, x - frontOffset, y - frontOffset, size, front);

}

void TextRenderer::RenderText(std::string text, int x, int y, int size, Color front, Color back)
{
	const char* newText = text.c_str();
	RenderText(newText, x, y, size, front, back);
}
