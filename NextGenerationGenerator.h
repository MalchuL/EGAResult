#pragma once
#include "ByteVector.h"
#include "ProportionalSelection.h"
#include <vector>
#include <map>
#include <algorithm>
using namespace std;



class NextGenerationGenerator
{
	double overlapCoef;
	AbstractSelection& selection;
public:
	double getOverlapCoef() { return overlapCoef; }
	void setOverlapCoef(double value) {
		overlapCoef = value;
	}
	void setSelection(AbstractSelection& value) {
		selection = value;
	}
	NextGenerationGenerator(double overlapCoef,AbstractSelection& selection) :overlapCoef(overlapCoef),selection(selection) {}
	vector<ByteVector> GenerateNextGeneration(const vector<ByteVector>& currentGeneration,const vector<ByteVector>& descendants,const vector<ByteVector>& mutants) {
		vector<ByteVector> nextGeneration = currentGeneration;
		int generationSize = nextGeneration.size();
		int excludeSize = overlapCoef * generationSize;
		
		if (excludeSize < 1)excludeSize = 1;
		if (excludeSize > generationSize)excludeSize = generationSize;
		//Исключим самые слабые элементы из текущего поколения
	//	random_shuffle(nextGeneration.begin(), nextGeneration.end());
		for (size_t i = 0; i < excludeSize; i++)
		{
			int minindex = 0;
			ByteVector minByte = nextGeneration.at(minindex);
			funcvalue mincost = selection.CalculateFitness(minByte);
			
			for (int index = 0;index < nextGeneration.size();index++) {
				ByteVector byte = nextGeneration.at(index);
				if(selection.CalculateFitness(byte)<mincost){
					mincost = selection.CalculateFitness(byte);
					minByte = byte;
					minindex = index;
				}
			}
			nextGeneration.erase(nextGeneration.begin() + minindex);
		}
		
	//	nextGeneration.erase(nextGeneration.begin(), nextGeneration.begin() + excludeSize);
		//Возьмем случайно некоторые элементы из объединения мутантов и потомков
		vector<ByteVector> reproducts;
		reproducts.insert(reproducts.end(), descendants.begin(), descendants.end());
		reproducts.insert(reproducts.end(), mutants.begin(), mutants.end());
		reproducts = selection.getGoodChilds(reproducts, excludeSize);
		/*random_shuffle(reproducts.begin(), reproducts.end());
		reproducts.erase(reproducts.begin() + excludeSize, reproducts.end());
		*/
		nextGeneration.insert(nextGeneration.end(), reproducts.begin(), reproducts.end());
		if (nextGeneration.size() != generationSize)throw 1;
		return nextGeneration;

	}
	~NextGenerationGenerator();
};

