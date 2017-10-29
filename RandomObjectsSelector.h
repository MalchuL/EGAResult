#pragma once
#include <vector>
using namespace std;
template<class T>
class RandomObjectsSelector
{
	vector<T*> objects;
public:
	T& getRandomObject() {
		return *(objects.at(rand() % objects.size()));
	}
	RandomObjectsSelector(vector<T*> objects):objects(objects) {

	}
};

