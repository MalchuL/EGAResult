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
		RandomObjectsSelector<AbstractStartPopulationGenerator> generator = RandomObjectsSelector<AbstractStartPopulationGenerator>({});
		switch (variant)
		{
		case 1:
			generator.getObjects().push_back(
				new DancigStartPopulationGenerator(maxWeight));
			break;
		case 2:
			generator.getObjects().push_back(
				new RandomStartPopulationGenerator(maxWeight, rand()));
			break;
		default:
			generator.getObjects().push_back(
				new DancigStartPopulationGenerator(maxWeight));
			generator.getObjects().push_back(
				new RandomStartPopulationGenerator(maxWeight, rand()));
			break;
		}
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
	vector<ByteVector> GenerateChilds(vector<ByteVector> parents, function func){
		//Сгенерируем детей разными способами
		RandomObjectsSelector<AbstractParentSelector> pairParentGenerator = RandomObjectsSelector<AbstractParentSelector>(
		{new InbridingParentSelector(),
		 new OutbridParentSelector(),
			new PossibleAssociableParentSelector(func)
		});
		//Применим кроссовер для получения потомков
		vector<ByteVector> childs;
		int byteLen = parents.at(0).getLen();
		RandomObjectsSelector<AbstractCrossover> crossoverGenerator = RandomObjectsSelector<AbstractCrossover>(
		{ new OnePointCrossover(),
			new	TwoPointCrossover((rand() % (byteLen / 2)) + 1),
			new RandomCrossover()
		});
		//Сгенерируем пары родителей
		vector<BytePair> parentPairs;
		//clog << "parents" << endl;
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
		//	clog << "p:" << endl;
		//	clog << parentPair.first << endl << parentPair.second << endl;
		//	clog << "c:"<<endl << child << endl;
		}

		return childs;

	}
	vector<ByteVector> GenerateMutants(vector<ByteVector> vectors) {
		int byteLen = vectors.at(0).getLen();
		RandomObjectsSelector<AbstractMutation> mutantGenerator = RandomObjectsSelector<AbstractMutation>(
		{new GeneticPointMutation(),
		new	InversionMutation(byteLen / 2 + 1),
			new	ByteInversionMutation(byteLen /	1.5 + 1) 
		});
		vector<ByteVector> mutants;
		//clog << "mutants" << endl;
		for(ByteVector vect:vectors){
		//	clog << "n:" << vect << endl;
			ByteVector mutant = mutantGenerator.getRandomObject().Mutate(vect);
			mutants.push_back(mutant);
		//	clog << "m:" << mutant << endl;
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
	bool VectorIsUnique(vector<ByteVector> vectors) {
		ByteVector checkVector = vectors.at(0);
		for (ByteVector vector : vectors) {
			if (vector != checkVector)return true;
		}
		return false;
	}
	int populationSize;
	int childsSize;
	int mutantSize;
	float nextGenerationOverlapCoef;
	float cForSelection;
	const int steps;
	int variant;
public:
	GeneticAlgorithm(int populationSize,int maxsteps,int variant):populationSize(populationSize),steps(maxsteps),variant(variant) {
		cout << variant << endl;
		cout << populationSize << endl;
		childsSize = populationSize * 15;
		mutantSize = 0.25*childsSize;
		nextGenerationOverlapCoef = 1.f / 3.f;
		cForSelection = 2;
	}
	ByteVector find(vector<BackpackObject> objectsVector, weightvalue maxWeight) {
		ObjectVector convertedVector;
		for (size_t i = 0; i < objectsVector.size(); i++)
		{
			convertedVector.push_back(IndexedBackpackObject(i, objectsVector[i]));
			clog << i << " weight:" << objectsVector[i].weight << " cost:" << objectsVector[i].cost << endl;
		}
		return find(convertedVector, maxWeight);
	}
	ByteVector find(ObjectVector objectsVector,weightvalue maxWeight) {

		//Генератор следующего поколения

		//Наша функция приспособленности
		function funcFitness = function(objectsVector);
		//Селекция
		//ProportionalSelection selection = ProportionalSelection(funcFitness, cForSelection);
		NextGenerationGenerator nextGenerationGenerator = NextGenerationGenerator(nextGenerationOverlapCoef, funcFitness);

		//Сгенерируем начальную популяцию
		vector<ByteVector> currentPopulation = GenerateStartPopulation(objectsVector, maxWeight);
		clog << "Start population" << endl;
		printVectorList(currentPopulation, funcFitness);
		clog << endl;
	//	cout << "Generations" << endl;
		int iter = 0;
		for (iter = 0; iter < steps; iter++)
		{
			{
				ByteVector max = findMaxInList(currentPopulation, funcFitness);
			//	cout << iter << " generation, max element: " << max << " cost: " << funcFitness.calculateFitness(max) << " weight: " << funcFitness.calculateWeight(max) << endl;
			}

			vector<ByteVector> childs = GenerateChilds(currentPopulation,funcFitness);
			//Выберем потомков для мутирования
			vector<ByteVector> childsForMutation;
			for (size_t i = 0; i < mutantSize; i++)
			{
				int randomIndex = rand() % childs.size();
				childsForMutation.push_back(childs.at(randomIndex));
				childs.erase(childs.begin() + randomIndex);

			}
			vector<ByteVector> mutants = GenerateMutants(childsForMutation);
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
			/*
			clog << "after Childs" << endl;
			printVectorList(childs, funcFitness);
			clog << "after Mutants" << endl;
			printVectorList(mutants, funcFitness);*/
			currentPopulation = nextGenerationGenerator.GenerateNextGeneration(currentPopulation, childs, mutants);
			clog << "Current population for "<< iter +1<<" generation" << endl;

			printVectorList(currentPopulation, funcFitness);
			clog << endl;
			if (!VectorIsUnique(currentPopulation)) {
				//cout << "Population is not unique" << endl;
				break;
			}
		}
		
		{
			ByteVector max = findMaxInList(currentPopulation, funcFitness);
			cout<<"variant:"<< variant<<" Iter:"<< iter <<" cost: " << funcFitness.calculateFitness(max) << endl;
		}
		return findMaxInList(currentPopulation, funcFitness);
		
	}

	~GeneticAlgorithm();
};

