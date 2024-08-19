#include "misc_manager.h"

void MiscManager::Unload()
{
	UnloadSound(checkPointSound);
}
void MiscManager::Setup(Entity& ref)
{
	playerRef = &ref;
	checkPointSound = LoadSound("Assets/Audio/SFX/Hit.mp3");
}
void MiscManager::ClearLists()
{
	checkPointList.clear();
	barrierList.clear();
	//barrier.Clear();
}
void MiscManager::CreateCheckPoint(int x, int y)
{
	CheckPoint newCheckPoint;
	newCheckPoint.Setup(Vector2((float)x, (float)y), *playerRef);
	checkPointList.push_back(newCheckPoint);
}
void MiscManager::CreateBarrierPoint(Vector2 pos)
{
	barrierList.push_back(pos);
	//barrier.AddBarrier(pos);
}
int MiscManager::UpdateCheckPoints()
{
	for (int i = 0; i < checkPointList.size(); i++)
	{
		if (checkPointList.at(i).Update())
		{
			
			PlaySound(checkPointSound);
			return i;
		}
	}
	return 4444;
}
void MiscManager::Render() 
{
	for (int i = 0; i < checkPointList.size(); i++)
	{
		checkPointList.at(i).Render();
	}
}