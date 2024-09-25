#pragma once
#include "raylib.h"
#include "scene.h"
#include "text_render.h"

class MainMenu : public Scene
{
private:

	const char* CURRENT_VERSION = "v0.2.1-beta";
	float screenWidth = 0.f;
	float sceenHeight = 0.f;
	Texture2D bg{};
	Texture2D title{};
	SCENE_TYPE nextScene = SCENE_TYPE::NONE;

	//bool isTxrLoaded = false;
	const int FONT_SIZE = 40;
	const int OFFSET = 160;
	const float BLINK_RATE = 0.5f;
	float blinkTimer = 0.f;
	bool showText = true;

	TextRenderer txtRend;

	Music menuSong{};
public:


	void LoadScene() override;
	void LeaveScene() override;
	bool Update() override;
	void Render() override;
	void RenderUI() override;

	void ChangeToLevel() { nextScene = SCENE_TYPE::LEVEL; }
	
	SCENE_TYPE GetNewScene() override { return nextScene; }

	void DrawBackground();
	//void LoadTextures();

};