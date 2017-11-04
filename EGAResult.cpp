// EGAResult.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "GeneticAlgorithm.h"
#include <fstream>
//#include "tests.h"

/*1     5    24
    2     9     4
    3    20    14
    4    29    10
    5    19    12
    6    30    15
    7    27    27
    8     9     8
    9    23    17
   10     6    13
   11    10    13
   12     9    19
   13    22    13
   14     9     7
   15     6     6*/
int main()
{
	srand(5);
	std::ofstream out("log.txt");
	std::clog.rdbuf(out.rdbuf());
	vector<BackpackObject> objects;
	int maxW = 65;
	vector<weightvalue> weights ={24, 4, 14, 10, 12, 15, 27, 8, 17, 13, 13, 19, 13, 7, 6};
	vector<weightvalue> costs = { 5, 9, 20, 29, 19,  30,  27, 9, 23,  6,  10,  9,  22,  9,  6 };
	cout << "Things" << endl;
	for (size_t i = 0; i < 50; i++)
	{
		costvalue cost =/* costs[i];*/ rand() % 29 + 1;
		weightvalue weight =/* weights[i];*/ rand() % 20 + 1;
		cout << i + 1 << " cost:" << cost << " weight:" << weight << endl;
		objects.push_back(BackpackObject(weight,cost));
		//objects.push_back(BackpackObject(weights[i],costs[i]));
	}
	cout << "Max weight:" << maxW << endl;
	cout << "Parents in populations:" << 50 << endl;
	cout << "Max iterations:"<<100 << endl;
	GeneticAlgorithm alg = GeneticAlgorithm(50,100);
	cout << alg.find(objects, maxW);
	getchar();
    return 0;
}

