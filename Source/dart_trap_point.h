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

	float timeAlive = 3.f;
	float speed = 10.f;
public:
	void Setup(Vector2 newPos, Entity& ref, Texture2D atlas, bool left);
	void Update(float dt); // Shoot bullets // Check collisions
	void Render(); // Render bullets
};