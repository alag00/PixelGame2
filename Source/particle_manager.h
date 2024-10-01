#pragma once
#include "particle.h"
#include <vector>

enum PARTICLE_TYPE
{
	FALLING_SNOW,
	FALLING_LEAVES,
	SWORD_CLASH,
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
	void Update(float dt);
	void Render();
};
