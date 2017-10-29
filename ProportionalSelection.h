#pragma once
#include "AbstractSelection.h"
class ProportionalSelection :
	public AbstractSelection
{
	const float c;
protected:
	virtual float CalculateProbability(ByteVector vector, int allsize, funcvalue allsum) {
		return (CalculateFitness(vector) + c) / (allsum + c*allsize);
	}
public:
	ProportionalSelection(function func, float c) :AbstractSelection(func),c(c) {
	}
	vector<ByteVector> getGoodChilds(vector<ByteVector> allChilds, int size) {
		vector<float> probabilities;
		funcvalue allsum = 0;
		for (ByteVector vector : allChilds) {
			allsum += CalculateFitness(vector);
		}
		for (size_t i = 0; i < allChilds.size(); i++)
		{
			probabilities.push_back(CalculateProbability(allChilds.at(i), allChilds.size(), allsum));
		}
		Roulette<ByteVector> roulette(allChilds, probabilities);
		vector<ByteVector> goodChilds;
		for (size_t i = 0; i < size; i++)
		{
			goodChilds.push_back(roulette.getRandomObject());
		}
		return goodChilds;

	}
	~ProportionalSelection();
};

