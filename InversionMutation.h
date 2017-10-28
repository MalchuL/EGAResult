#pragma once
#include "AbstractMutation.h"
class InversionMutation :
	public AbstractMutation
{
	int inversionSize;
public:
	InversionMutation(int inversionSize) :inversionSize(inversionSize) {}
	ByteVector Mutate(ByteVector vector) {
		ByteVector mutatedVector(vector);
		int startIndex = rand() % (vector.getLen() - inversionSize);
		for (size_t i = startIndex; i < startIndex+inversionSize; i++)
		{
			mutatedVector.setByte(2*startIndex + inversionSize - i - 1, vector.getByte(i));
		}
		return mutatedVector;
	}
	~InversionMutation();
};

