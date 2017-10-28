#pragma once
#include "AbstractStartPopulationGenerator.h"
#include <algorithm>    // std::random_shuffle
#include <cstdlib>      // std::rand, std::srand
using namespace std;
class RandomStartPopulationGenerator :
	public AbstractStartPopulationGenerator
{
public:
	RandomStartPopulationGenerator(weightvalue maxWeight, int randomSeed) :AbstractStartPopulationGenerator(maxWeight) { srand(randomSeed); }
	ByteVector Generate(ObjectVector objectVector)
	{	

		random_shuffle(objectVector.begin(), objectVector.end());
		weightvalue currentWeight = 0;
		ByteVector generatedVector(objectVector.size());
		
		
		for (auto object : objectVector) {
			
			if (currentWeight+object.object.weight<=maxWeight)
			{
				currentWeight += object.object.weight;
				generatedVector.setByte(object.index, 1);
			}
			clog << object.index << " " << object.object.weight << " " << object.object.cost << " curW:" << currentWeight << endl;
		}
		return generatedVector;
	}
	~RandomStartPopulationGenerator();
};

