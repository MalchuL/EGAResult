#pragma once
#include "AbstractSelection.h"
class TournirSelection:public AbstractSelection
{
	int tournirSize;
public:
	TournirSelection(function func,int tournirSize) :AbstractSelection(func), tournirSize(tournirSize){}
	vector<ByteVector> getGoodChilds(vector<ByteVector> allChilds, int size) {
		vector<ByteVector> goodChilds;

		for (size_t i = 0; i < size; i++)
		{
			random_shuffle(allChilds.begin(), allChilds.end());
			vector<ByteVector> vect(allChilds.begin(), allChilds.begin() + tournirSize);
			ByteVector maxByteVector = allChilds.at(0);
			funcvalue maxValue = CalculateFitness(maxByteVector);
			for (size_t i = 0; i < allChilds.size(); i++)
			{
				if (CalculateFitness(allChilds.at(i)) > maxValue) {
					maxByteVector = allChilds.at(i);
					maxValue = CalculateFitness(allChilds.at(i));
				}
			}
			goodChilds.push_back(maxByteVector);
		}
		
		return goodChilds;

	}
	~TournirSelection();
};

