#include "scene_manager.h"

SceneManager::SceneManager() {
	MainMenu* mainMenu = new MainMenu();
	currentScene = mainMenu;
	currentScene->LoadScene();
}
SceneManager::~SceneManager()
{
	delete currentScene;
	currentScene = nullptr;
}
void SceneManager::Update() {

	if (currentScene->Update())
	{
		ChangeScene(currentScene->GetNewScene());
	}
	currentScene->Render();
}
void SceneManager::ChangeScene(SCENE_TYPE sceneType)
{
	currentScene->LeaveScene();
	delete currentScene;
	currentScene = nullptr;

	switch (sceneType)
	{
	case SCENE_TYPE::MAIN_MENU:
		MainMenu* mainMenu;
		mainMenu = new MainMenu();
		currentScene = mainMenu;
		currentScene->LoadScene();
		break;
	case SCENE_TYPE::LEVEL:
	{

		LevelManager* level;
		level = new LevelManager();
		currentScene = level;
		currentScene->LoadScene();
		break;
	}
	case SCENE_TYPE::CREDITS:
		break;
	case SCENE_TYPE::NONE:
		break;
	}
}
