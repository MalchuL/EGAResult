#pragma once
#include "ByteVector.h"
#include "Selection.h"
#include "RandomObjectsSelector.h"
#include <vector>
#include <map>
#include <algorithm>
using namespace std;



class NextGenerationGenerator
{
	double overlapCoef;
	function& func;

	ByteVector findMaxByteVector(const vector<ByteVector>& vectors) {
		ByteVector maxVector = vectors.at(0);
		funcvalue maxValue = func.calculateFitness(maxVector);
		for (ByteVector vector : vectors) {
			funcvalue value = func.calculateFitness(vector);
			if (value > maxValue) {
				maxValue = value;
				maxVector = vector;
			}
		}
		return maxVector;
	
	}
public:
	double getOverlapCoef() { return overlapCoef; }
	void setOverlapCoef(double value) {
		overlapCoef = value;
	}
	void setFunc(function& value) {
		func = value;
	}
	NextGenerationGenerator(double overlapCoef,function& func) :overlapCoef(overlapCoef), func(func) {}
	vector<ByteVector> GenerateNextGeneration(const vector<ByteVector>& currentGeneration,const vector<ByteVector>& descendants,const vector<ByteVector>& mutants) {
		//Наш селектор
		RandomObjectsSelector<AbstractSelection> selectionSelector = RandomObjectsSelector<AbstractSelection>({
			new TournirSelection(func, currentGeneration.size() / 6 + 1),
			new ProportionalSelection(func,0)
		});

		vector<ByteVector> nextGeneration = currentGeneration;
		int generationSize = nextGeneration.size();
		int excludeSize = overlapCoef * generationSize;
		
		if (excludeSize < 1)excludeSize = 1;
		if (excludeSize > generationSize)excludeSize = generationSize;
		//Исключим самые слабые элементы из текущего поколения

		for (size_t i = 0; i < excludeSize; i++)
		{
			int minindex = 0;
			ByteVector minByte = nextGeneration.at(minindex);
			funcvalue mincost = func.calculateFitness(minByte);
			
			for (int index = 0;index < nextGeneration.size();index++) {
				ByteVector byte = nextGeneration.at(index);
				if(func.calculateFitness(byte)<mincost){
					mincost = func.calculateFitness(byte);
					minByte = byte;
					minindex = index;
				}
			}
			nextGeneration.erase(nextGeneration.begin() + minindex);
		}


		//Возьмем некоторые элементы из объединения мутантов и потомков
		vector<ByteVector> reproducts;
		reproducts.insert(reproducts.end(), descendants.begin(), descendants.end());
		reproducts.insert(reproducts.end(), mutants.begin(), mutants.end());

		//Найдем максимального из объединения потомков и мутантов
		ByteVector maxVector = findMaxByteVector(reproducts);

		reproducts = selectionSelector.getRandomObject().getGoodChilds(reproducts, excludeSize-1);

		nextGeneration.insert(nextGeneration.end(), maxVector);
		nextGeneration.insert(nextGeneration.end(), reproducts.begin(), reproducts.end());
		if (nextGeneration.size() != generationSize)throw 1;
		return nextGeneration;

	}
	~NextGenerationGenerator();
};

