#include "barrier_point.h"

void BarrierPoint::AddBarrier(Vector2 pos)
{
	Vector2 newPos = pos;
	barrierList.push_back(newPos);
}
void BarrierPoint::SetActive(bool newValue) 
{ 
	active = newValue; 
}
void BarrierPoint::Clear()
{
	barrierList.clear();
}