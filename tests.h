#pragma once
#include "StartPopulation.h"

void testPopulation() {
	ObjectVector vect;
	for (size_t i = 0; i < 10; i++)
	{
		weightvalue weight = rand() % 10 + 1;
		costvalue cost = rand() % 15 + 1;
		clog << i << " "<<weight << " "<<cost << " " << endl;
		vect.push_back(IndexedBackpackObject(i, BackpackObject(weight, cost)));
	}
	AbstractStartPopulationGenerator* generator =new DancigStartPopulationGenerator(30);
	clog << "Dancig" << endl;
	for (size_t i = 0; i < 10; i++)
	{
		clog << generator->Generate(vect) << endl;
	}
	generator =new RandomStartPopulationGenerator(30,20);
	clog << "Random" << endl;
	for (size_t i = 0; i < 10; i++)
	{
		clog << generator->Generate(vect) << endl;
	}

}