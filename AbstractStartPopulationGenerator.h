#pragma once
#include "ByteVector.h"
#include "IndexedBackpackObject.h"

class AbstractStartPopulationGenerator
{

protected:
	weightvalue maxWeight;
public:

	AbstractStartPopulationGenerator(weightvalue maxWeigth) :maxWeight(maxWeigth)
	{
	};
	virtual ByteVector Generate(ObjectVector) = 0;

};

