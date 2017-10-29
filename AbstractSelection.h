#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include "ByteVector.h"
#include "Roulette.h"
#include "IndexedBackpackObject.h"

class FitnessCalculator {
private:
	ObjectVector objectVector;
public:
	FitnessCalculator(ObjectVector objectVector) :objectVector(objectVector) {}
	costvalue calculateFitness(ByteVector vector) {
		costvalue currentCost = 0;
		for (IndexedBackpackObject object : objectVector) {
			if (vector.getByte(object.index)) {
				currentCost += object.object.cost;
			}
		}
		return currentCost;
	}
	weightvalue calculateWeight(ByteVector vector) {
		costvalue currentWeight = 0;
		for (IndexedBackpackObject object : objectVector) {
			if (vector.getByte(object.index)) {
				currentWeight += object.object.weight;
			}
		}
		return currentWeight;
	}
};

typedef float funcvalue;
typedef FitnessCalculator function;
class AbstractSelection
{
private:
	function func;
protected:


public:
	funcvalue CalculateFitness(ByteVector vector) {
		return func.calculateFitness(vector);
	}
	AbstractSelection(function func) :func(func) {};
	virtual vector<ByteVector> getGoodChilds(vector<ByteVector> allChilds, int size) = 0;
	~AbstractSelection();
};

