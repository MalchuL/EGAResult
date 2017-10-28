#pragma once
#include <utility>
#include <vector>
#include "ByteVector.h"
#include <algorithm>
#include "SetSizeException.h"
using namespace std;
typedef std::pair<ByteVector, ByteVector> BytePair;
class AbstractParentSelector
{
public:
	AbstractParentSelector();
	BytePair SelectParents(vector<ByteVector> byteVectorList) {
		if (byteVectorList.size() < 2)throw SetSizeException();
		random_shuffle(byteVectorList.begin(), byteVectorList.end());
		ByteVector firstParent(byteVectorList.at(0));
		ByteVector secondParent = SelectPair(firstParent,byteVectorList);


	}

	virtual ByteVector SelectPair(ByteVector firstParent, vector<ByteVector>& potencialParents) = 0;
	~AbstractParentSelector();
};

