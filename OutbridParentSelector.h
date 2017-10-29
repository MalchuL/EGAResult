#pragma once
#include "AbstractParentSelector.h"
#include "ByteVectorMath.h"
class OutbridParentSelector :
	public AbstractParentSelector
{
private:

	float SecondParentProbability(ByteVector firstParent, ByteVector secondParent) {
		int length = ByteVectorMath::HemmingLength(firstParent, secondParent);
		return length / (float)firstParent.getLen();
	}
public:


	OutbridParentSelector();
	~OutbridParentSelector();
};

