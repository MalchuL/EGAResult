#pragma once
#include <vector>
#include <map>
#include <algorithm>
#include "ByteVector.h"
#include "Roulette.h"
typedef float funcvalue;
typedef map<ByteVector, funcvalue> function;
class AbstractSelection
{
private:
	function func;
protected:
	funcvalue CalculateFitness(ByteVector vector) {
		return func.at(vector);
	}

public:
	AbstractSelection(function func) :func(func) {};
	virtual vector<ByteVector> getGoodChilds(vector<ByteVector> allChilds, int size) = 0;
	~AbstractSelection();
};

