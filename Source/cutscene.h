#pragma once
#include "raylib.h"
#include "animation.h"
#include "dialogue.h"
#include "text_render.h"

class Cutscene
{
private:
public:
	virtual void Setup(Vector2& ref) { (void)ref; };

	virtual bool Update(float dt) { (void)dt; return false; };
	virtual void Render(){};
	virtual void RenderUI() {};
	virtual void Unload() {};
};

class CastleCutscene : public Cutscene
{
private:
	Vector2* camRef = nullptr;

	float scale = 3.f;

	Texture2D playerIdle{};
	Texture2D playerWalk{};
	Animator playerAnim;
	Vector2 playerPos{ 0.f,0.f };
	Vector2 playerSize{ 0.f,0.f };

	Texture2D enemyIdle{};
	Animator enemyAnim;
	Vector2 enemyPos{ 0.f,0.f };
	Vector2 enemySize{ 0.f,0.f };

	Texture2D playerPort{};
	

	Texture2D enemyListenPort{};
	Texture2D enemySpeakPort{};
	Dialogue dialogue;

	TextRenderer txtRend;

	int cutsceneStage = 0;

	//const float PAUSE_TIMER = 1.f;
	float pauseTimer = 0.3f;
	bool enemyFlipped = false;
	const float ENEMY_SCARED_SPEED = 5.f;

public:
	void Setup(Vector2& ref) override;
	void SetupStageOne();
	void SetupStageTwo();
	bool Update(float dt) override;
	void Render() override;
	void RenderUI() override;
	void Unload() override;
};

class GraveyardCutscene : public Cutscene
{
private:
	Vector2* camRef = nullptr;

	float scale = 3.f;

	Texture2D playerIdle{};
	Texture2D playerWalk{};
	Animator playerAnim;
	Vector2 playerPos{ 0.f,0.f };
	Vector2 playerSize{ 0.f,0.f };

	Texture2D enemyIdle{};
	Texture2D enemyWalk{};
	Texture2D enemyRefill{};
	Animator enemyAnim;
	Vector2 enemyPos{ 0.f,0.f };
	Vector2 enemySize{ 0.f,0.f };
	Color enemyCol = GREEN;

	Texture2D playerPort{};


	Texture2D enemyListenPort{};
	Texture2D enemySpeakPort{};
	Dialogue dialogue;
	TextRenderer txtRend;

	int cutsceneStage = 1;
public:
	void Setup(Vector2& ref) override;
	void SetupStageOne();
	void SetupStageTwo();
	void SetupStageThree();
	void SetupStageFour();
	void SetupStageFive();
	void SetupStageSix();
	void SetupStageSeven();
	void SetupStageEight();
	void SetupStageNine();
	bool Update(float dt) override;
	void Render() override;
	void RenderUI() override;
	void Unload() override;
};