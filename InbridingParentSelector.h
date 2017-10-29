#pragma once
#include "AbstractParentSelector.h"
class InbridingParentSelector :
	public AbstractParentSelector
{
protected:
	float Probability(ByteVector firstParent, ByteVector secondParent) {
		int length = ByteVectorMath::HemmingLength(firstParent, secondParent);
		if (length == 0)return 0;
		return 1/(float)length ;
	}
public:
	InbridingParentSelector();
	~InbridingParentSelector();
};

