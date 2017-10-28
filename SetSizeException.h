#pragma once
#include "vcruntime_exception.h"
class SetSizeException :
	public std::exception
{
public:
	SetSizeException();
	~SetSizeException();
};

