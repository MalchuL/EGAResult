#pragma once
#include "BackpackObject.h"
class IndexedBackpackObject
{
public:
	BackpackObject object;
	int index;
	IndexedBackpackObject(int index, BackpackObject& object) :index(index), object(object) {};

	IndexedBackpackObject& operator=(const IndexedBackpackObject& other) // copy assignment
	{
		this->index = other.index;
		this->object = other.object;
		return *this;
	}

	IndexedBackpackObject(const IndexedBackpackObject& other) :index(other.index), object(other.object){
	};

	~IndexedBackpackObject();
};

