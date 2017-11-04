#pragma once
#include "AbstractSelection.h"
class TournirSelection:public AbstractSelection
{
	float tournirSizeCoef;
public:
	TournirSelection(function func,float tournirSizeCoef) :AbstractSelection(func), tournirSizeCoef(tournirSizeCoef){}
	vector<ByteVector> getGoodChilds(vector<ByteVector> allChilds, int size) {
		vector<ByteVector> goodChilds;
		int tournirSize = allChilds.size()*tournirSizeCoef + 1;
		if (tournirSize > allChilds.size())tournirSize = allChilds.size();
		//cout << tournirSize << endl;
		if (tournirSize <= 0)throw 1;
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

