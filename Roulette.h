#pragma once
#include <vector>
#include <iostream>
using namespace std;
template<class T>
class Roulette
{
	vector<float> probabilities;
	float probalityScale;
	vector<T> objects;
public:
	Roulette(vector<T> objects, vector<float> probabilities):objects(objects) {
		if (objects.size() != probabilities.size())throw 1;
		this->probabilities = vector<float>();
		float currentProbality=0;
		for (size_t i = 0; i < probabilities.size(); i++)
		{
			currentProbality += probabilities.at(i);
			this->probabilities.push_back(currentProbality);
			clog << this->objects.at(i) << " " << this->probabilities.at(i) << endl;
		}
		probalityScale = currentProbality;
	}
	T getRandomObject() {
		float randomValue = abs((float)rand()) / RAND_MAX * probalityScale;
		clog << randomValue << endl;
		for (size_t i = 0; i < probabilities.size(); i++)
		{
			if (randomValue<probabilities.at(i)) {
				return objects.at(i);
			}
		}
	}
	~Roulette() {}
};

