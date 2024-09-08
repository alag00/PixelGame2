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
	grappPointList.clear();
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
void MiscManager::CreateGrapplingPoint(int x, int y)
{
	GrapplingPoint newGrappPoint;
	newGrappPoint.Setup(Vector2((float)x, (float)y), *playerRef);
	grappPointList.push_back(newGrappPoint);
}
int MiscManager::UpdateCheckPoints()
{
	if (checkPointList.empty())
	{
		return 4444;
	}
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

int MiscManager::UpdateGrapplingPoints()
{
	// If pressed Q 
	// Get nearest grappling point in range which the player faces
	if (grappPointList.empty())
	{
		return 4444;
	}
	for (int i = 0; i < grappPointList.size(); i++)
	{
		grappPointList.at(i).Update();	
		grappPointList.at(i).SetIdeal(false);
	}
	int idealIndex = GetMostViableGrapplingIndex();
	if (idealIndex != 4444)
	{
		grappPointList.at(idealIndex).SetIdeal(true);
	}
	if (IsKeyPressed(KEY_Q))
	{
		return idealIndex;
	}
	return 4444;
}
void MiscManager::Render() 
{
	for (int i = 0; i < checkPointList.size(); i++)
	{
		checkPointList.at(i).Render();
	}
	for (int i = 0; i < grappPointList.size(); i++)
	{
		grappPointList.at(i).Render();
	}
}

int MiscManager::GetMostViableGrapplingIndex()
{
	bool rightSide = playerRef->GetLookSide();

	std::vector<int> validIndexes{};
	for (int i = 0; i < grappPointList.size(); i++)
	{
		if (rightSide && grappPointList.at(i).GetPos().x < playerRef->GetCenter().x || !rightSide && grappPointList.at(i).GetPos().x > playerRef->GetCenter().x)
		{
			continue;
		}
		
			int newIndex = i;
			validIndexes.push_back(newIndex);
		
	}
	if (validIndexes.empty())
	{
		return 4444;
	}
	int closestIndex = 0;
	for (int i = 0; i < validIndexes.size(); i++)
	{
		//grappPointList.at(validIndexes.at(i).Distance());
		if (grappPointList.at(validIndexes.at(closestIndex)).GetDistance() > grappPointList.at(validIndexes.at(i)).GetDistance())
		{
			closestIndex = i;
		}
	}
	closestIndex = validIndexes.at(closestIndex);
	
	/*
	for (int i = 0; i < grappPointList.size(); i++)
	{
		if (rightSide && grappPointList.at(i).GetPos().x < playerRef->GetCenter().x || !rightSide && grappPointList.at(i).GetPos().x > playerRef->GetCenter().x)
		{
			continue;
		}
		if (grappPointList.at(closestIndex).GetDistance() > grappPointList.at(i).GetDistance())
		{
			closestIndex = i;
		}
	}
	*/
	if (!grappPointList.at(closestIndex).GetInRange())
	//if (!grappPointList.at(closestIndex).GetInRange() || rightSide && grappPointList.at(closestIndex).GetPos().x < playerRef->GetCenter().x || !rightSide && grappPointList.at(closestIndex).GetPos().x > playerRef->GetCenter().x)//if (!grappPointList.at(closestIndex).GetInRange())
	{
		return 4444;
	}
	return closestIndex;
}