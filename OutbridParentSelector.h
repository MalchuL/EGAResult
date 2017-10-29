#pragma once
#include "AbstractParentSelector.h"
#include "ByteVectorMath.h"
class OutbridParentSelector :
	public AbstractParentSelector
{
private:

	float Probability(ByteVector firstParent, ByteVector secondParent) {
		int length = ByteVectorMath::HemmingLength(firstParent, secondParent);
		return length / (float)firstParent.getLen();
	}
public:


	OutbridParentSelector();
	~OutbridParentSelector();
};

