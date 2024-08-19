#pragma once
#include "raylib.h"
#include <vector>
#include "entity.h"
#include "check_point.h"
//#include "barrier_point.h"

class MiscManager
{
private:
	Entity* playerRef = nullptr;
	std::vector<CheckPoint> checkPointList{};
	//BarrierPoint barrier;

	std::vector<Vector2> barrierList{};
	//bool active = false;

	Sound checkPointSound{};
public:
	void Unload();
	void Setup(Entity& ref);
	void ClearLists();
	void CreateCheckPoint(int x, int y);
	void CreateBarrierPoint(Vector2 pos);
	std::vector<CheckPoint> GetCheckPointList() { return checkPointList; }
	std::vector<Vector2> GetBarrierList() { return barrierList; }
	int UpdateCheckPoints();
	void UpdateBarrierPoints();
	void Render();
};