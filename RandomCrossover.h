#pragma once
#include "AbstractCrossover.h"
class RandomCrossover :
	public AbstractCrossover
{
public:
	RandomCrossover();
	ByteVector Crossover(ByteVector firstVector, ByteVector secondVector) {
		//int point = secondVector.getLen() / 4 + (rand() % (3 * secondVector.getLen() / 4 - secondVector.getLen() / 4 + 1));
		ByteVector result(secondVector);
		for (size_t i = 0; i < secondVector.getLen(); i++)
		{
			if (rand() % 2) {
				result.setByte(i, firstVector.getByte(i));
			}
		}
		return result;
	}
	~RandomCrossover();
};

