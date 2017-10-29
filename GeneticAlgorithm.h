#pragma once
#include <vector>
#include "BackpackObject.h"
#include "RandomObjectsSelector.h"
#include "StartPopulation.h"
#include "Selection.h"
#include "ParentSelector.h"
#include "Crossover.h"
#include "Mutation.h"
#include "NextGenerationGenerator.h"
#include "GenotypeModificationLimitationProcessing.h"
typedef vector<costvalue> costvector;
typedef vector<weightvalue> weightvector;
//typedef vector<BackpackObject> ObjectVector;

using namespace std;



class GeneticAlgorithm
{

	vector<ByteVector> GenerateStartPopulation(ObjectVector objectsVector,weightvalue maxWeight) {
		vector<ByteVector> startPopulation;
		RandomObjectsSelector<AbstractStartPopulationGenerator> generator = RandomObjectsSelector<AbstractStartPopulationGenerator>({new DancigStartPopulationGenerator(maxWeight),new RandomStartPopulationGenerator(maxWeight,rand()) });
		for (size_t i = 0; i < populationSize; i++)
		{
			startPopulation.push_back(generator.getRandomObject().Generate(objectsVector));
		}
		return startPopulation;
	}

	void printVectorList(vector<ByteVector> list, function funcFitness) {
		for (ByteVector vect : list) {
			clog << vect <<" weight:"<<funcFitness.calculateWeight(vect) <<" fitness:" << funcFitness.calculateFitness(vect) << endl;
		}
	}
	vector<ByteVector> GenerateChilds(vector<ByteVector> parents){
		//Сгенерируем детей разными способами
		RandomObjectsSelector<AbstractParentSelector> pairParentGenerator = RandomObjectsSelector<AbstractParentSelector>(
		{new InbridingParentSelector(),
		 new OutbridParentSelector()
		});
		//Применим кроссовер для получения потомков
		vector<ByteVector> childs;
		int byteLen = parents.at(0).getLen();
		RandomObjectsSelector<AbstractCrossover> crossoverGenerator = RandomObjectsSelector<AbstractCrossover>(
		{ new OnePointCrossover(),
			new	TwoPointCrossover((rand() % (byteLen / 2)) + 1) });
		//Сгенерируем пары родителей
		vector<BytePair> parentPairs;
		clog << "parents" << endl;
		for (size_t i = 0; i < childsSize; i++)
		{
			BytePair parentPair = pairParentGenerator.getRandomObject().SelectParents(parents);
			ByteVector child(byteLen);
			if (rand() % 2 == 1) {
				child = crossoverGenerator.getRandomObject().Crossover(parentPair.first, parentPair.second);
			}
			else
			{
				child = crossoverGenerator.getRandomObject().Crossover(parentPair.second, parentPair.first);
			}
			childs.push_back(child);
			clog << "p:" << endl;
			clog << parentPair.first << endl << parentPair.second << endl;
			clog << "c:"<<endl << child << endl;
		}

		return childs;

	}
	vector<ByteVector> GenerateMutants(vector<ByteVector> vectors) {
		int byteLen = vectors.at(0).getLen();
		RandomObjectsSelector<AbstractMutation> mutantGenerator = RandomObjectsSelector<AbstractMutation>(
		{new GeneticPointMutation(),
		new	InversionMutation(byteLen / 2 + 1),
			new	ByteInversionMutation(byteLen /	1.5 + 1) });
		vector<ByteVector> mutants;
		for(ByteVector vect:vectors){
			mutants.push_back(mutantGenerator.getRandomObject().Mutate(vect));
		}
		return mutants;
	}

	ByteVector findMaxInList(vector<ByteVector> list, function funcFitness) {
		ByteVector maxVector = list.at(0);
		funcvalue maxValue = funcFitness.calculateFitness(maxVector);
		for (ByteVector vect : list) {
			funcvalue value = funcFitness.calculateFitness(vect);
			if (value>maxValue) {
				maxValue = value;
				maxVector = vect;

			}
		}
		return maxVector;
	}

	int populationSize;
	int childsSize;
	int mutantSize;
	float nextGenerationOverlapCoef;
	float cForSelection;
	const int steps = 10;
public:
	GeneticAlgorithm(int populationSize):populationSize(populationSize) {
		childsSize = populationSize * 3;
		mutantSize = childsSize*3;
		nextGenerationOverlapCoef = 1.f / 3.f;
		cForSelection = populationSize;
	}
	ByteVector find(vector<BackpackObject> objectsVector, weightvalue maxWeight) {
		ObjectVector convertedVector;
		for (size_t i = 0; i < objectsVector.size(); i++)
		{
			convertedVector.push_back(IndexedBackpackObject(i, objectsVector[i]));
		}
		return find(convertedVector, maxWeight);
	}
	ByteVector find(ObjectVector objectsVector,weightvalue maxWeight) {

		//Генератор следующего поколения

		//Наша функция приспособленности
		function funcFitness = function(objectsVector);
		//Селекция
		ProportionalSelection selection = ProportionalSelection(funcFitness, cForSelection);
		NextGenerationGenerator nextGenerationGenerator = NextGenerationGenerator(nextGenerationOverlapCoef, selection);

		//Сгенерируем начальную популяцию
		vector<ByteVector> currentPopulation = GenerateStartPopulation(objectsVector, maxWeight);
		printVectorList(currentPopulation, funcFitness);
		clog << endl;
		for (size_t i = 0; i < steps; i++)
		{


			vector<ByteVector> childs = GenerateChilds(currentPopulation);
			vector<ByteVector> mutants = GenerateMutants(childs);
			GenotypeModificationLimitationProcessing LimitationProcessor = GenotypeModificationLimitationProcessing(objectsVector, maxWeight);
			//Преобразуем до допустимых
		/*
			clog << "before Childs" << endl;
			printVectorList(childs, funcFitness);
			clog << "before Mutants" << endl;
			printVectorList(mutants, funcFitness);*/
			for (size_t i = 0; i < childs.size(); i++)
			{
				childs[i] = LimitationProcessor.ModifyToAllowed(childs[i]);
			}
			for (size_t i = 0; i < mutants.size(); i++)
			{
				mutants[i] = LimitationProcessor.ModifyToAllowed(mutants[i]);
			}
			clog << "after Childs" << endl;
			printVectorList(childs, funcFitness);
			clog << "after Mutants" << endl;
			printVectorList(mutants, funcFitness);
			currentPopulation = nextGenerationGenerator.GenerateNextGeneration(currentPopulation, childs, mutants);
			clog << "Current Population" << endl;
			printVectorList(currentPopulation, funcFitness);
			clog << endl;
		}
		

		return findMaxInList(currentPopulation, funcFitness);
		
	}

	~GeneticAlgorithm();
};

