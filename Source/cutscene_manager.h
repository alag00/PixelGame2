#pragma once

#include "raylib.h"
#include "cutscene.h"

class CutsceneManager
{
private:
	Vector2* camRef = nullptr;
	Cutscene* currentCutscene = nullptr;
public:
	~CutsceneManager();
	void Setup(Vector2& ref);
	void SwitchCutscene(int cutsceneID);
	bool Update(float dt);
	void Render();
	void RenderUI();
};