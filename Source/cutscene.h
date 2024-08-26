#pragma once
#include "raylib.h"
#include "animation.h"
#include "dialogue.h"

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

	Texture2D playerIcon{};
	Texture2D enemyIcon{};
	Dialogue dialogue;

	int cutsceneStage = 0;
public:
	void Setup(Vector2& ref) override;
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
	Texture2D playerJump{};
	Animator playerAnim;
	Vector2 playerPos{ 0.f,0.f };
	Vector2 playerSize{ 0.f,0.f };

	Texture2D enemyIdle{};
	Texture2D enemyRest{};
	Animator enemyAnim;
	Vector2 enemyPos{ 0.f,0.f };
	Vector2 enemySize{ 0.f,0.f };

	Texture2D playerIcon{};
	Texture2D enemyIcon{};
	Dialogue dialogue;
public:
	void Setup(Vector2& ref) override;
	bool Update(float dt) override;
	void Render() override;
	void RenderUI() override;
	void Unload() override;
};