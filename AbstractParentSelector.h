#pragma once
#include <utility>
#include <vector>
#include "ByteVector.h"
#include "ByteVectorMath.h"
#include <algorithm>
#include "SetSizeException.h"
#include "Roulette.h"
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
		ByteVector secondParent = SelectPairToFirstVector(firstParent,byteVectorList);
		return BytePair(firstParent, secondParent);

	}
	virtual float Probability(ByteVector firstParent, ByteVector secondParent) = 0;
	ByteVector SelectPairToFirstVector(ByteVector firstParent,const vector<ByteVector>& potencialParents) {
		vector<ByteVector> parents;
		vector<float> probabilities;
		for(ByteVector vector:potencialParents)
		{
			int length = ByteVectorMath::HemmingLength(firstParent, vector);
			if (length > 0) {
				parents.push_back(vector);
				probabilities.push_back(Probability(firstParent, vector));
			}
		}
		Roulette<ByteVector> roulette = Roulette<ByteVector>(parents, probabilities);
		ByteVector secondParent = roulette.getRandomObject();
		return secondParent;
	
	}
	~AbstractParentSelector();
};

