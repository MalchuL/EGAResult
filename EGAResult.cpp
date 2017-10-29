// EGAResult.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "GeneticAlgorithm.h"
#include <fstream>
//#include "tests.h"


int main()
{
	std::ofstream out("log.txt");
	std::clog.rdbuf(out.rdbuf());
	vector<BackpackObject> objects;
	int maxW = 500;
	vector<int> costs = { 26,23,12,10,2,27,8,5,11,22,20,11,9,25,21 };
	vector<int> weights = { 2,8,19,3,28,12,5,8,1,19,3,24,9,5,25 };
	for (size_t i = 0; i < 50; i++)
	{
		objects.push_back(BackpackObject(rand()%29+1, rand()%20+1));
	}
	GeneticAlgorithm alg = GeneticAlgorithm(100,30);
	cout << alg.find(objects, maxW);
	getchar();
    return 0;
}

