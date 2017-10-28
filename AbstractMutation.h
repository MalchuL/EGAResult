#pragma once
#include "ByteVector.h"
class AbstractMutation
{
public:
	AbstractMutation();
	virtual ByteVector Mutate(ByteVector vector) = 0;
	~AbstractMutation();
};

