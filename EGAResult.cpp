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
	for (size_t i = 0; i < 50; i++)
	{
		objects.push_back(BackpackObject(rand()%29+1, rand()%20+1));
	}
	GeneticAlgorithm alg = GeneticAlgorithm(100,100);
	cout << alg.find(objects, maxW);
	getchar();
    return 0;
}

