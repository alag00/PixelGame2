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
	std::vector<ParticleEffect*> particleList{};
public:
	~ParticleManager();
	void ClearList();
	void QueueParticle(PARTICLE_TYPE type);
	void Update(float dt);
	void Render();
};
