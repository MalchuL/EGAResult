#pragma once
#include "StartPopulation.h"
#include "OnePointCrossover.h"
#include "TwoPointCrossover.h"
#include "GeneticPointMutation.h"
#include "InversionMutation.h"
#include "Roulette.h"
#include "OutbridParentSelector.h"
#include "InbridingParentSelector.h"
#include "NextGenerationGenerator.h"
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
void testMutation() {
	ByteVector vector1(0b000000, 6);
	GeneticPointMutation mutation1 = GeneticPointMutation();
	clog << mutation1.Mutate(vector1)<<endl;

	vector1 = ByteVector(0b101010, 6);
	InversionMutation mutation2 = InversionMutation(4);
	clog << mutation2.Mutate(vector1)<<endl;
}
void testRoulette() {
	vector<int> objects;
	vector<float> probabilities;
	vector<int> counts;
	for (size_t i = 1; i < 10; i++)
	{
		objects.push_back(i);
		probabilities.push_back(1 / (float)i);
		counts.push_back(0);
	}
	Roulette<int> roul = Roulette<int>(objects, probabilities);
	for (size_t i = 0; i < 10000; i++)
	{
		counts[roul.getRandomObject() - 1] += 1;;
	}
	for (size_t i = 0; i < 9; i++)
	{
		clog<<i+1<<" "<< counts[i]<<endl;
	}
}
/*void testNextGeneration() {
	vector<ByteVector> currentGeneration;
	vector<ByteVector> desc;
	vector<ByteVector> mutants;
	for (size_t i = 0; i < 20; i++)
	{
		currentGeneration.push_back(ByteVector(0, 6));
		desc.push_back(ByteVector(0b111111, 6));
		mutants.push_back(ByteVector(0b101010, 6));
	}
	NextGenerationGenerator generator = NextGenerationGenerator(0.5);
	vector<ByteVector> nextGeneration = generator.GenerateNextGeneration(currentGeneration, desc, mutants);
	for (size_t i = 0; i < nextGeneration.size(); i++)
	{
		clog << nextGeneration.at(i) << endl;
	}


}*/
void testParentSelector() {
	vector<ByteVector> vectors;
	const int len = 6;
	for (size_t i = 0; i < 1<<len; i++)
	{
		vectors.push_back(ByteVector(i,len));
		vectors.push_back(ByteVector(i, len));
	}
	OutbridParentSelector outselector;
	clog << "outselector" << endl;
	for (size_t i = 0; i < 20; i++)
	{
		BytePair pair = outselector.SelectParents(vectors);
		clog << pair.first << " " << pair.second << endl;
	}
	InbridingParentSelector inselector;
	clog << "inselector" << endl;
	for (size_t i = 0; i < 20; i++)
	{
		BytePair pair = inselector.SelectParents(vectors);
		clog << pair.first << " " << pair.second << endl;
	}

}
void testCrossover() {
	ByteVector vector1(0b111000, 6);
	ByteVector vector2(0b000111, 6);
	OnePointCrossover crossover = OnePointCrossover(3);

	clog << crossover.Crossover(vector1, vector2)<<endl;
	clog << crossover.Crossover(vector2, vector1)<<endl;

	vector1 = ByteVector(0b111111,6);
	vector2 = ByteVector(0b000000, 6);
	TwoPointCrossover crossover2 = TwoPointCrossover(2, 4);
	crossover2.setFirstPoint(5);
	clog << crossover2.Crossover(vector1, vector2) << endl;
	clog << crossover2.Crossover(vector2, vector1) << endl;
}