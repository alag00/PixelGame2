#include "misc_manager.h"

void MiscManager::Unload()
{
	UnloadSound(checkPointSound);

	UnloadTexture(dartTxr);

	for (int i = 0; i < miscSetSize; i++)
	{
		for (int j = 0; j < miscObjSize; j++)
		{
			UnloadTexture(txrList[i][j]);
		}
	}
}
void MiscManager::Setup(Entity& ref)
{
	checkPointSound = LoadSound("Assets/Audio/SFX/Checkpoint.mp3");
	dartTxr = LoadTexture("Assets/Particles/DartAtlas.png");

	txrList[0][0] = LoadTexture("Assets/MiscObjectsTextures/Rock1.png");
	txrList[0][1] = LoadTexture("Assets/MiscObjectsTextures/Rock2.png");
	txrList[0][2] = LoadTexture("Assets/MiscObjectsTextures/Bush1.png");

	txrList[1][0] = LoadTexture("Assets/MiscObjectsTextures/Tree1.png");
	txrList[1][1] = LoadTexture("Assets/MiscObjectsTextures/Tree2.png");
	txrList[1][2] = LoadTexture("Assets/MiscObjectsTextures/Bush1.png");

	txrList[2][0] = LoadTexture("Assets/MiscObjectsTextures/Statue1.png");
	txrList[2][1] = LoadTexture("Assets/MiscObjectsTextures/Statue2.png");
	txrList[2][2] = LoadTexture("Assets/MiscObjectsTextures/Statue3.png");

	txrList[3][0] = LoadTexture("Assets/MiscObjectsTextures/SpookyTree1.png");
	txrList[3][1] = LoadTexture("Assets/MiscObjectsTextures/SpookyTree2.png");
	txrList[3][2] = LoadTexture("Assets/MiscObjectsTextures/SpookyTree3.png");

	txrList[4][0] = txrList[0][0];
	txrList[4][1] = txrList[0][0];
	txrList[4][2] = txrList[0][0];

	playerRef = &ref;
}
void MiscManager::ClearLists()
{
	checkPointList.clear();
	barrierList.clear();
	grappPointList.clear();

	for (int i = 0; i < dartTrapList.size(); i++)
	{
		delete dartTrapList.at(i);
		dartTrapList.at(i) = nullptr;
	}
	dartTrapList.clear();

	for (int i = 0; i < objectList.size(); i++)
	{
		delete objectList.at(i);
		objectList.at(i) = nullptr;
	}
	objectList.clear();
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
void MiscManager::CreateDartTrapPoint(int x, int y, bool left)
{
	DartTrap* newDartTrap = new DartTrap();
	newDartTrap->SetTexture(dartTxr);
	newDartTrap->Setup(Vector2((float)x, (float)y), *playerRef, left);
	dartTrapList.push_back(newDartTrap);
}

void MiscManager::CreateObject(int x, int y, int level, int index)
{
	int worldMisc = 0;
	switch (level)
	{
	case 1:
	case 9:
		worldMisc = 0;
		break;
	case 2:
	case 3:
		worldMisc = 1;
		break;
	case 4:
	case 5:
		worldMisc = 2;
		break;
	case 6:
	case 10:
		worldMisc = 4;
		break;
	case 7:
	case 8:
		worldMisc = 3;
		break;
	}
	BackgroundObject* newObject = new BackgroundObject();
	newObject->SetTextue(txrList[worldMisc][index]);
	newObject->Setup(Vector2((float)x, (float)y));
	objectList.push_back(newObject);
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
void MiscManager::UpdateDartTrapsPoints(float dt)
{
	if (dartTrapList.empty())
	{
		return;
	}
	for (int i = 0; i < dartTrapList.size(); i++)
	{
		dartTrapList.at(i)->Update(dt);
	}
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
	for (int i = 0; i < dartTrapList.size(); i++)
	{
		dartTrapList.at(i)->Render();
	}
	for (int i = 0; i < objectList.size(); i++)
	{
		objectList.at(i)->Render();
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