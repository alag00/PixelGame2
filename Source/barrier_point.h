#pragma once
#include <vector>
#include "raylib.h"

class BarrierPoint
{
private:
	std::vector<Vector2> barrierList{};
	bool active = false;		
public:
	std::vector<Vector2> GetList() {return barrierList;}
	void AddBarrier(Vector2 pos);
	void SetActive(bool newValue);
	void Clear();

};