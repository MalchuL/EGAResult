#pragma once
#include <vector>
using namespace std;
template<class T>
class RandomObjectsSelector
{
	vector<T&> objects;
public:
	T& getRandomObject() {
		return objects.at(rand() % objects.size());
	}
	RandomObjectsSelector(vector<T&> objects) {
		this->objects = vector<T&>();
		for (size_t i = 0; i < objects.size(); i++)
		{
			this->objects.push_back(objects.at(i));
		}
	}
};

