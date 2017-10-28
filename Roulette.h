#pragma once
#include <vector>
using namespace std;
template<class T>
class Roulette
{
public:
	Roulette(vector<T> objects,vector<float> probabilities);
	~Roulette();
};

