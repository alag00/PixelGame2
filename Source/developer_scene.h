#pragma once
#include "raylib.h"
#include "scene.h"
#include "animation.h"
#include "screen_effects.h"


class DeveloperScene: public Scene
{
private:

	float screenWidth = 0.f;
	float screenHeight = 0.f;

	SCENE_TYPE nextScene = SCENE_TYPE::NONE;
	Texture2D atlas{};
	Texture2D devNameTxr{};
	Animator anim;
	const float CUSTOM_FPS = 6.f; // 12 defualt

	float startTimer = 1.f;

	const float SIZE_IN_PIXELS = 64.f;
	const float SCALE = 6.f;
	Rectangle dst = { 0.f,0.f, 0.f, 0.f};
	Rectangle nameDst = { 0.f,0.f, 0.f, 0.f };

	const Color BACKGROUND_COLOR = {28,28,28,255};

	Effect filter;
	bool endScene = false;
	Camera2D cam;

public:
	void LoadScene() override;
	void LeaveScene() override;
	bool Update() override;
	void Render() override;

	void ChangeToMainMenu() { nextScene = SCENE_TYPE::MAIN_MENU; }
	SCENE_TYPE GetNewScene() override { return nextScene; }

	bool CheckEvent();

};