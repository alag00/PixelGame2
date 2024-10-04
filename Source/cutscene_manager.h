#pragma once

#include "raylib.h"
#include "cutscene.h"

class CutsceneManager
{
private:
	Vector2* camRef = nullptr;
	Effect* filterRef = nullptr;
	Cutscene* currentCutscene = nullptr;
public:
	~CutsceneManager();
	void Setup(Vector2& ref, Effect& filter);
	void SwitchCutscene(int cutsceneID);
	bool Update(float dt);
	void Render();
	void RenderUI();
};