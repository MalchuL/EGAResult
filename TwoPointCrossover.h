#pragma once
#include "AbstractCrossover.h"
class TwoPointCrossover :
	public AbstractCrossover
{
	int firstPoint;
	int secondPoint;
public:
	int getFirstPoint() { return firstPoint; }
	int getSecondPoint() { return secondPoint; }
	void setFirstPoint(int firstPoint) {
		if (firstPoint < getSecondPoint())
		{ 
			this->firstPoint = firstPoint;
		}
		else
		{
			throw 1;
		}
	}
	void setSecondPoint(int secondPoint) {
		if (secondPoint > getFirstPoint()) 
		{ 
			this->secondPoint = secondPoint; 
		}
		else
		{
			throw 1;
		}
	}
	TwoPointCrossover(int firstPoint, int secondPoint) {
		if (firstPoint < secondPoint) {
			this->firstPoint = firstPoint;
			this->secondPoint = secondPoint;
		}
		else
		{
			throw 1;
		}
	}
	~TwoPointCrossover();
};

