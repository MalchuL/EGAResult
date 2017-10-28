#pragma once
#include <vector>
#include "BackpackObject.h"
#include "AbstractStartPopulationGenerator.h"
#include "DancigStartPopulationGenerator.h"
#include "RandomStartPopulationGenerator.h"
typedef vector<costvalue> costvector;
typedef vector<weightvalue> weightvector;
//typedef vector<BackpackObject> ObjectVector;

using namespace std;

class GeneticAlgorithm
{
public:
	GeneticAlgorithm();
	~GeneticAlgorithm();
};

