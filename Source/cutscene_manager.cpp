#include "cutscene_manager.h"


CutsceneManager::~CutsceneManager()
{
	currentCutscene->Unload();
	delete currentCutscene;
	currentCutscene = nullptr;

	camRef = nullptr;
}

void CutsceneManager::Setup(Vector2& ref)
{
	camRef = &ref;
}

void CutsceneManager::SwitchCutscene(int cutsceneID)
{
	if (currentCutscene != nullptr)
	{
		currentCutscene->Unload();
		delete currentCutscene;
		currentCutscene = nullptr;
	}

	switch (cutsceneID)
	{
	case 0:
		return;
	case 1:
		currentCutscene = new CastleCutscene();
		break;
	case 2:
		currentCutscene = new GraveyardCutscene();
		break;
	}
	currentCutscene->Setup(*camRef);
}

bool CutsceneManager::Update(float dt)
{
	return currentCutscene->Update(dt);
}

void CutsceneManager::Render()
{
	currentCutscene->Render();
}

void CutsceneManager::RenderUI()
{
	currentCutscene->RenderUI();
}
