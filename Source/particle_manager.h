#pragma once
#include "particle.h"
#include <vector>

enum PARTICLE_TYPE
{
	FALLING_SNOW,
	FALLING_LEAVES,
	SWORD_CLASH,
	BREATH_STEAM,
};
class ParticleManager
{
private:
	Camera2D* camRef = nullptr;
	std::vector<ParticleEffect*> particleList{};
public:
	~ParticleManager();
	void SetCameraRef(Camera2D& ref) { camRef = &ref; }
	void ClearList();
	void QueueParticle(PARTICLE_TYPE type, Vector2 position);
	void QueueParticleBreathSteam(Vector2 pos, Vector2 vel);
	void Update(float dt);
	void Render();
};
