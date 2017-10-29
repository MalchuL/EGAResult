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
protected:
	virtual ByteVector SelectFirstParent(const vector<ByteVector>& byteVectorList) {

		return byteVectorList.at(rand() % byteVectorList.size());
	}
	virtual float SecondParentProbability(ByteVector firstParent, ByteVector secondParent) = 0;

	ByteVector SelectPairToFirstVector(ByteVector firstParent, const vector<ByteVector>& potencialParents) {
		vector<ByteVector> parents;
		vector<float> probabilities;
		//clog << potencialParents.size();
		for (ByteVector vector : potencialParents)
		{
			int length = ByteVectorMath::HemmingLength(firstParent, vector);
	//		clog << length << endl;
			if (length > 0) {
	//			clog << "1" << endl;
				parents.push_back(vector);
				probabilities.push_back(SecondParentProbability(firstParent, vector));
			}
		}
		if (parents.size() == 0)throw 1;
		//clog << "f";
		Roulette<ByteVector> roulette = Roulette<ByteVector>(parents, probabilities);
		ByteVector secondParent = roulette.getRandomObject();
		return secondParent;

	}
public:
	AbstractParentSelector();
	BytePair SelectParents(vector<ByteVector> byteVectorList) {
		if (byteVectorList.size() < 2)throw SetSizeException();
	//	random_shuffle(byteVectorList.begin(), byteVectorList.end());
		ByteVector firstParent(SelectFirstParent(byteVectorList));
		ByteVector secondParent = SelectPairToFirstVector(firstParent,byteVectorList);
		return BytePair(firstParent, secondParent);

	}

	~AbstractParentSelector();
};

