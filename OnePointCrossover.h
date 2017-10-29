#pragma once
#include "AbstractCrossover.h"
class OnePointCrossover :
	public AbstractCrossover
{
	//int point;
public:
	//int getPoint() { return point; }
	//void setPoint(int point) { this->point = point; }
	OnePointCrossover() {
	}
	ByteVector Crossover(ByteVector firstVector, ByteVector secondVector) {
		int point = secondVector.getLen()/4 + (rand() % (3*secondVector.getLen() / 4 - secondVector.getLen() / 4 + 1));
		ByteVector result(secondVector.getLen());
		for (size_t i = 0; i < point; i++)
		{
			result.setByte(i,firstVector.getByte(i));
		}
		for (size_t i = point; i < secondVector.getLen(); i++)
		{
			result.setByte(i, secondVector.getByte(i));
		}
		return result;
	}
	~OnePointCrossover();
};

