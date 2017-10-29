#pragma once
#include "AbstractSelection.h"
class TournirSelection:public AbstractSelection
{
public:
	TournirSelection(function func) :AbstractSelection(func) {}
	~TournirSelection();
};

