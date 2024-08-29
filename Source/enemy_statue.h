#pragma once

#include "enemy.h"
#include "animation.h"

class WeepingAngelEnemy : public Enemy
{
private:
	Entity* playerRef = nullptr;
	bool active = false;
	DECISION dec = DECISION::IDLE;
	bool lookLeft = false;
	Rectangle attackBox{ 0.f,0.f,0.f,0.f };
	Texture2D atlas{};
	Animator anim;
	Vector2 size{ 0.f,0.f };
	float scale = 3.f;
public:
	~WeepingAngelEnemy();
	void SetTextures(Texture2D txr);
	void SetAudio(Sound death, Sound init, Sound swing);
	void SetPlayerRef(Entity& ref) { playerRef = &ref; }
	void Setup();

	void Sense();
	void Decide();
	void Act(float dt);
	void Move(float dt);
	void Render();

};