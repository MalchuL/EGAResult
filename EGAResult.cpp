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
	std::ofstream out_iter("iterations.txt");
	std::cout.rdbuf(out_iter.rdbuf());
	vector<GeneticAlgorithm> genalg;
	for (int i = 1; i <= 3; i++)
	{
		genalg.push_back(GeneticAlgorithm(50, 30, i));
	}
	for (size_t i = 0; i < 50; i++)
	{
		vector<BackpackObject> objects;
		for (size_t i = 0; i < 50; i++)
		{
			costvalue cost =/* costs[i];*/ rand() % 24 +10;
			weightvalue weight =/* weights[i];*/ rand() % 20 + 1;
		//	cout << i + 1 << " cost:" << cost << " weight:" << weight << endl;
			objects.push_back(BackpackObject(weight, cost));
			//objects.push_back(BackpackObject(weights[i],costs[i]));
		}
		for (int i = 0; i < 3; i++)
		{
			genalg.at(i).find(objects, 400);
		}
		cout << "-------------------" << endl;
	}
	getchar();
    return 0;
}

