#pragma once
#include "AbstractStartPopulationGenerator.h"
#include <algorithm>

using namespace std;
class DancigStartPopulationGenerator :
	public AbstractStartPopulationGenerator
{
private:
	static bool compare(IndexedBackpackObject& first,IndexedBackpackObject& second) {
		//Взять из первой пары и из второй только их стоимости и веса и сравнить
		return first.object.cost / first.object.weight < second.object.cost / second.object.weight;

	}
public:
	DancigStartPopulationGenerator(weightvalue maxWeight) :AbstractStartPopulationGenerator(maxWeight) {}
	ByteVector Generate(ObjectVector objectVector)
	{

		costvalue currentCost = 0;
		weightvalue currentWeight = 0;
		ByteVector generatedVector(objectVector.size());

		std::sort(objectVector.begin(), objectVector.end(),compare);
		std::reverse(objectVector.begin(), objectVector.end());

		for (size_t i = 0; i < objectVector.size(); i++)
		{

			if (currentWeight + objectVector.at(i).object.weight <= maxWeight) {
				currentWeight += objectVector.at(i).object.weight;
				generatedVector.setByte(objectVector.at(i).index,1);
			}
			else
			{
				//Иначе мб уже с минимальными вессами, но с самой маленькой стоимостью
			}
			clog << objectVector.at(i).index << " " << objectVector.at(i).object.weight << " " << objectVector.at(i).object.cost << " " << objectVector.at(i).object.cost / objectVector.at(i).object.weight << " curW:" << currentWeight << endl;

		}

		return generatedVector;
	}
	~DancigStartPopulationGenerator();
};
