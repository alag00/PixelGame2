#pragma once
#include "raylib.h"
#include <vector>
#include "entity.h"
#include "check_point.h"
#include "grappling_point.h"
#include "dart_trap_point.h"
#include "background_object.h"
#include "hurt_block.h"


class MiscManager
{
private:
	Entity* playerRef = nullptr;
	std::vector<CheckPoint> checkPointList{};
	std::vector<Vector2> barrierList{};
	std::vector<GrapplingPoint> grappPointList{};
	std::vector<DartTrap*> dartTrapList{};
	Texture2D dartTxr{};

	Sound checkPointSound{};
	std::vector<HurtBlock> hurtBlockList{};

	std::vector<BackgroundObject*> objectList{};
	static const int miscSetSize = 5;
	static const int miscObjSize = 3;
	Texture2D txrList[miscSetSize][miscObjSize]{}; 
	const int FAIL_VALUE = 4444;

public:
	void Unload();
	void Setup(Entity& ref);
	void ClearLists();

	void CreateCheckPoint(int x, int y);
	void CreateBarrierPoint(Vector2 pos);
	void CreateGrapplingPoint(int x, int y);
	void CreateDartTrapPoint(int x, int y, bool left);
	void CreateObject(int x, int y, int world, int index);
	void CreateHurtBlock(int x, int y);

	std::vector<CheckPoint> GetCheckPointList() { return checkPointList; }
	std::vector<Vector2> GetBarrierList() { return barrierList; }
	std::vector<GrapplingPoint> GetGrapPointList() { return grappPointList; }
	std::vector<DartTrap*> GetDartPointList() { return dartTrapList; }
	int GetMostViableGrapplingIndex();

	int UpdateCheckPoints();
	
	int UpdateGrapplingPoints();
	void UpdateDartTrapsPoints(float dt);
	bool UpdateHurtBlocks();
	void Render();
};