#include "particle_manager.h"

ParticleManager::~ParticleManager()
{
	ClearList();
}

void ParticleManager::ClearList()
{
	for (int i = 0; i < particleList.size(); i++)
	{
		delete particleList.at(i);
		particleList.at(i) = nullptr;
	}
	particleList.clear();
}

void ParticleManager::QueueParticle(PARTICLE_TYPE type, Vector2 position)
{
	switch (type)
	{
	case PARTICLE_TYPE::SWORD_CLASH:
	{
		SwordClashParticle* swordClash = new SwordClashParticle(position, *camRef);
		particleList.push_back(swordClash);
	}
		break;
	case PARTICLE_TYPE::FALLING_LEAVES:
	{
		LeafParticle* leafFall = new LeafParticle(*camRef);
		particleList.push_back(leafFall);
	}
		break;
	case PARTICLE_TYPE::FALLING_SNOW:
	{
		SnowParticle* snowFall = new SnowParticle(*camRef);
		particleList.push_back(snowFall);
	}
		break;
	case PARTICLE_TYPE::BREATH_STEAM:
	{
		SteamParticle* breathSteam = new SteamParticle(position, *camRef);
		particleList.push_back(breathSteam);
	}
	break;
	}

}

void ParticleManager::Update(float dt)
{
	if (particleList.empty())
	{
		return;
	}
	std::vector<int> deadIndexes{};
	for (int i = 0; i < particleList.size(); i++)
	{
		if (!particleList.at(i)->IsActivated())
		{
			int index = i;
			deadIndexes.push_back(index);
			continue;
		}
		particleList.at(i)->Update(dt);
	}
	if (deadIndexes.empty())
	{
		return;
	}

	for (int i = 0; i < deadIndexes.size(); i++)
	{
		delete particleList.at(deadIndexes.back());
		particleList.at(deadIndexes.back()) = nullptr;

		particleList.erase(particleList.begin() + deadIndexes.back());
		deadIndexes.pop_back();
	}
}

void ParticleManager::Render()
{
	if (particleList.empty())
	{
		return;
	}
	for (int i = 0; i < particleList.size(); i++)
	{
		particleList.at(i)->Render();
	}
}
