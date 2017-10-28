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

	ByteVector Crossover(ByteVector firstVector, ByteVector secondVector) {
		ByteVector result(secondVector.getLen());
		for (size_t i = 0; i < getFirstPoint(); i++)
		{
			result.setByte(i, firstVector.getByte(i));
		}
		for (size_t i = getFirstPoint(); i < getSecondPoint(); i++)
		{
			result.setByte(i, secondVector.getByte(i));
		}
		for (size_t i = getSecondPoint(); i < secondVector.getLen(); i++)
		{
			result.setByte(i, firstVector.getByte(i));
		}
		return result;
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

