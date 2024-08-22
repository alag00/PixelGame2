#pragma once
enum class SCENE_TYPE
{
	NONE = 0,
	MAIN_MENU = 1,
	LEVEL = 2,
	CREDITS = 3,
	//Etc....
};

class Scene {
private:
public:
	virtual void LoadScene() { };
	virtual bool Update() { return false; };
	virtual void Render() {};
	virtual void RenderUI() {};
	virtual SCENE_TYPE GetNewScene() { return SCENE_TYPE::NONE; };
	virtual void LeaveScene() { };
};