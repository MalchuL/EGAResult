#pragma once
#include "ByteVector.h"
class AbstractCrossover
{
public:
	AbstractCrossover();
	virtual ByteVector CrossOver(ByteVector firstParent, ByteVector secondParent) = 0;
	~AbstractCrossover();
};

