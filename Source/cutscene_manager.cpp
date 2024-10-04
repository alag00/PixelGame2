#include "cutscene_manager.h"


CutsceneManager::~CutsceneManager()
{
	currentCutscene->Unload();
	delete currentCutscene;
	currentCutscene = nullptr;

	camRef = nullptr;
}

void CutsceneManager::Setup(Vector2& newCamRef, Effect& newFilterRef)
{
	camRef = &newCamRef;
	filterRef = &newFilterRef;
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
		currentCutscene = new IntroCutscene(*filterRef);
		break;
	case 2:
		currentCutscene = new CastleCutscene();
		break;
	case 3:
		currentCutscene = new CatCutscene();
		break;
		// Boss Cutscenes
	case -1:
		currentCutscene = new CastleBossCutscene();
		break;
	case -2:
		currentCutscene = new MansionBossCutscene();
		break;
	case -3:
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
