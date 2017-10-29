#pragma once
#include "IndexedBackpackObject.h"
#include "AbstractStartPopulationGenerator.h"
#include <vector>
#include <algorithm>

using namespace std;
class GenotypeModificationLimitationProcessing
{	
	weightvalue maxWeight;
	ObjectVector objectVector;
public:

	GenotypeModificationLimitationProcessing(ObjectVector objectVector, weightvalue maxWeight) :objectVector(objectVector), maxWeight(maxWeight) {}
	ByteVector ModifyToAllowed(ByteVector vector) {
		//Посчитаем вес
		weightvalue currentWeight = 0;
		ObjectVector weightedObjects;
		for (IndexedBackpackObject object : objectVector) {
			if (vector.getByte(object.index)) {
				currentWeight += object.object.weight;
				weightedObjects.push_back(object);
			}
		}
		while (currentWeight>maxWeight||weightedObjects.size()>0)
		{
			int index = rand() % weightedObjects.size();
			IndexedBackpackObject object = weightedObjects.at(index);
			currentWeight -= object.object.weight;
			vector.setByte(object.index, 0);
			weightedObjects.erase(weightedObjects.begin() + index);
		}
		if (currentWeight > maxWeight)throw 1;
		return vector;
	}
	~GenotypeModificationLimitationProcessing();
};

