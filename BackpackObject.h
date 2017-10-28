#pragma once
typedef float costvalue;
typedef float weightvalue;
class BackpackObject
{
public:
	weightvalue weight;
	costvalue cost;
	BackpackObject(weightvalue weight, costvalue cost) :weight(weight), cost(cost) {};
	~BackpackObject();
};

