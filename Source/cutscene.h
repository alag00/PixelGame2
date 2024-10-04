#pragma once
#include "raylib.h"
#include "animation.h"
#include "dialogue.h"
#include "text_render.h"
#include "screen_effects.h"
#include <cmath>

class Cutscene
{
private:
	const float BLINK_RATE = 0.5f;
	float blinkTimer = 0.f;
	bool showSkipText = true;
	TextRenderer txtRend;
	float barThickness = 100.f;
public:
	virtual void Setup(Vector2& ref) { (void)ref; };

	virtual bool Update(float dt) { (void)dt; return false; };
	virtual void Render(){};
	virtual void RenderUI() {};
	virtual void Unload() {};
	void UpdateSkipText(float dt);
	void RenderSkipText();
};

class IntroCutscene : public Cutscene
{
private:
	Vector2* camRef = nullptr;
	Effect* filter = nullptr;
	float scale = 3.f;

	Texture2D playerFall{};
	Texture2D playerRise{};
	Animator playerAnim;

	Vector2 playerPos{ 0.f,0.f };
	Vector2 playerSize{ 0.f,0.f };

	Texture2D angelTxr{};
	Vector2 angelPos{ 0.f,0.f };
	float angelYOrigin = 0.f;
	Vector2 angelSize{ 0.f,0.f };
	Color angelCol = WHITE;
	//Texture2D angelTxr2{};

	Texture2D angelPort{};
	Dialogue dialogue;

	int cutsceneStage = 0;

	bool hasFadeOut = false;
	float speed = 10.f;

	const float PAUSE_TIME = 1.0f;
	float pauseTimer = PAUSE_TIME;
	float progress = 0.f;
public:
	IntroCutscene(Effect& filterRef);
	void Setup(Vector2& ref) override;
	void SetupStageOne();
	void SetupStageFour();
	bool Update(float dt) override;
	void Render() override;
	void RenderUI() override;
	void Unload() override;


};

class CastleBossCutscene : public Cutscene
{
	// lvl 4
	// player walks past statue(boss), boss picks up player and throws her back
private:
public:
	void Setup(Vector2& ref) override;
	bool Update(float dt) override;
	void Render() override;
	void RenderUI() override;
	void Unload() override;
};

class CastleCutscene : public Cutscene
{
	// lvl 5, tile trigger
	// angel shows up, 
private:
	Vector2* camRef = nullptr;
	float scale = 3.f;

	Texture2D playerIdle{};
	Texture2D playerWalk{};
	Animator playerAnim;
	Texture2D playerPort{};

	Vector2 playerPos{ 0.f,0.f };
	Vector2 playerSize{ 0.f,0.f };

	Texture2D angelTxr1{};
	Texture2D angelTxr2{};
	Vector2 angelPos{ 0.f,0.f };
	float angelYOrigin = 0.f;
	Vector2 angelSize{ 0.f,0.f };
	Color angelCol = WHITE;
	//Texture2D angelTxr2{};

	Texture2D angelPort1{};
	Texture2D angelPort2{};
	Dialogue dialogue;

	int cutsceneStage = 0;

	float speed = 10.f;

	const float PAUSE_TIME = 1.0f;
	float pauseTimer = PAUSE_TIME;
	float progress = 0.f;

	bool hasRevealed = false;
public:
	void Setup(Vector2& ref) override;
	void SetupStageThree();
	void SetupStageFour();
	bool Update(float dt) override;
	void Render() override;
	void RenderUI() override;
	void Unload() override;
};

class CatCutscene : public Cutscene
{
	// lvl 7, level start
private:

	Vector2* camRef = nullptr;
	float scale = 3.f;

	Texture2D playerIdle{};
	Texture2D playerWalk{};
	Animator playerAnim;

	Vector2 playerPos{ 0.f,0.f };
	Vector2 playerSize{ 0.f,0.f };

	Texture2D catAtlas{};
	Animator catAnim;
	Vector2 catPos{ 0.f,0.f };
	Vector2 catSize{ 0.f,0.f };

	Texture2D playerPort{};
	Texture2D catPort{};
	Dialogue dialogue;

	int cutsceneStage = 0;

public:
	void Setup(Vector2& ref) override;
	void SetupStageTwo();
	bool Update(float dt) override;
	void Render() override;
	void RenderUI() override;
	void Unload() override;
};

class MansionBossCutscene : public Cutscene
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

