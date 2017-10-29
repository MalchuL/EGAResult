#pragma once
#include "ByteVector.h"
class AbstractCrossover
{
public:
	AbstractCrossover() {}
	virtual ByteVector Crossover(ByteVector firstParent, ByteVector secondParent) = 0;
	~AbstractCrossover();
};

