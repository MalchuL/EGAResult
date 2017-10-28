#pragma once
#include "ByteVector.h"
#include "IndexedBackpackObject.h"
//������������� � ��������
#include <vector>
typedef vector<IndexedBackpackObject> ObjectVector;

class AbstractStartPopulationGenerator
{

protected:
	weightvalue maxWeight;
public:

	AbstractStartPopulationGenerator(weightvalue maxWeigth);
	virtual ByteVector Generate(ObjectVector) = 0;
	~AbstractStartPopulationGenerator();
};

