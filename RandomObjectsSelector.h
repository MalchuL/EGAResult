#pragma once
#include <vector>
using namespace std;
template<class T>
class RandomObjectsSelector
{
	vector<T*> objects;
public:
	vector<T*>& getObjects() {
		return objects;
	}
	T& getRandomObject() {
		return *(objects.at(rand() % objects.size()));
	}
	RandomObjectsSelector(vector<T*> objects):objects(objects) {

	}
	~RandomObjectsSelector() {
		for (size_t i = 0; i < objects.size(); i++)
		{
			delete objects[i];
		}
	}
};

