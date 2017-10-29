#pragma once
#include "AbstractParentSelector.h"
#include "Selection.h"
#include "Roulette.h"
class PossibleAssociableParentSelector :
	public AbstractParentSelector
{
	function func;
protected:
	float SecondParentProbability(ByteVector firstParent, ByteVector secondParent) {
		int length = ByteVectorMath::HemmingLength(firstParent, secondParent);
		if (length == 0)return 0;
		return func.calculateFitness(secondParent)/ func.calculateFitness(firstParent);
	}
	ByteVector SelectFirstParent(const vector<ByteVector>& byteVectorList) {

		funcvalue sum = 0;
		for (ByteVector vector : byteVectorList) {
			sum += func.calculateFitness(vector);
		}
		vector<float> probabilities;
		for (size_t i = 0; i < byteVectorList.size(); i++)
		{
			probabilities.push_back(func.calculateFitness(byteVectorList.at(i)) / sum);
		}
		Roulette<ByteVector> roulette(byteVectorList, probabilities);
		return roulette.getRandomObject();
	}
public:
	PossibleAssociableParentSelector(function func) :func(func) {}

	~PossibleAssociableParentSelector();
};

