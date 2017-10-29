#pragma once
#include "AbstractCrossover.h"
class TwoPointCrossover :
	public AbstractCrossover
{
	int dispersion;
	//int secondPoint;
public:
	//int getFirstPoint() { return firstPoint; }
	//int getSecondPoint() { return secondPoint; }
	/*void setFirstPoint(int firstPoint) {
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
	}*/

	ByteVector Crossover(ByteVector firstVector, ByteVector secondVector) {
		ByteVector result(secondVector.getLen());
		int firstPoint = rand() % (secondVector.getLen() - dispersion);
		int secondPoint = firstPoint + dispersion;
		for (size_t i = 0; i < firstPoint; i++)
		{
			result.setByte(i, firstVector.getByte(i));
		}
		for (size_t i = firstPoint; i < secondPoint; i++)
		{
			result.setByte(i, secondVector.getByte(i));
		}
		for (size_t i = secondPoint; i < secondVector.getLen(); i++)
		{
			result.setByte(i, firstVector.getByte(i));
		}
		return result;
	}

	TwoPointCrossover(int dispersion):dispersion(dispersion) {

	}
	~TwoPointCrossover();
};

