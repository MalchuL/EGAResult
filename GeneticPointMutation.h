#pragma once
#include "AbstractMutation.h"

class GeneticPointMutation :
	public AbstractMutation
{
public:
	GeneticPointMutation();
	ByteVector Mutate(ByteVector vector) {
		int swapIndex = rand() % vector.getLen();
		vector.setByte(swapIndex, !vector.getByte(swapIndex));
		return vector;
	}
	~GeneticPointMutation();
};

