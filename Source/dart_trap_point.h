#pragma once
#include "raylib.h"
#include "entity.h"
#include "animation.h"

class DartTrap
{
private:
	Entity* playerRef = nullptr;

	Vector2 pos{0.f,0.f};
	Vector2 bulletPos{ 0.f,0.f };

	Animator anim;
	bool active = true;
	float timeAlive = 0.f;
	float speed = 10.f;
public:
	~DartTrap();
	void Setup(Vector2 newPos, Entity& ref, bool left);
	void SetTexture(Texture2D txr);
	void Update(float dt); 
	void Render(); 
};