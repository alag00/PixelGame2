#pragma once
#include "raylib.h"
#include "animation.h"
class Cutscene
{
private:
public:
	virtual void Setup(Vector2& ref) { (void)ref; };
	virtual bool Update(float dt) { (void)dt; return false; };
	virtual void Render(){};
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
public:
	void Setup(Vector2& ref) override;
	bool Update(float dt) override;
	void Render() override;
	void Unload() override;
};

class GraveyardCutscene : public Cutscene
{
private:
public:
	void Setup(Vector2& ref) override;
	bool Update(float dt) override;
	void Render() override;
	void Unload() override;
};