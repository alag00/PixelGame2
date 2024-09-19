#pragma once
#include "raylib.h"
#include "scene.h"
class MainMenu : public Scene
{
private:
	int width = 0;
	int height = 0;
	Texture2D bg{};

	SCENE_TYPE nextScene = SCENE_TYPE::NONE;

	bool isTxrLoaded = false;
public:


	void LoadScene() override;
	void LeaveScene() override;
	bool Update() override;
	void Render() override;
	void RenderUI() override;

	void ChangeToLevel() { nextScene = SCENE_TYPE::LEVEL; }
	
	SCENE_TYPE GetNewScene() override { return nextScene; }

	void DrawBackground();
	void LoadTextures();

};