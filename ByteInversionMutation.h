#pragma once
#include "AbstractMutation.h"
class ByteInversionMutation :
	public AbstractMutation
{
	int inversionSize;
public:
	ByteInversionMutation(int inversionSize) :inversionSize(inversionSize) {}
	ByteVector Mutate(ByteVector vector) {
		ByteVector mutatedVector(vector);
		int startIndex = rand() % (vector.getLen() - inversionSize);
		for (size_t i = startIndex; i < startIndex + inversionSize; i++)
		{
			mutatedVector.setByte(i, !vector.getByte(i));
		}
		return mutatedVector;
	}
	~ByteInversionMutation();
};

