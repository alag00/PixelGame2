#include "scene_manager.h"

SceneManager::SceneManager() {
	//Setup();
}
SceneManager::~SceneManager()
{
	delete currentScene;
	currentScene = nullptr;
}
void SceneManager::Setup()
{
	// Normal
	//DeveloperScene* devLogo = new DeveloperScene();
	//currentScene = devLogo;
	//currentScene->LoadScene();

	// Debug
	LevelManager* debug = new LevelManager();
	currentScene = debug;
	currentScene->LoadScene();
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
