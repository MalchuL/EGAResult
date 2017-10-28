#include "stdafx.h"
#include "IllegalVectorSizeException.h"


exceptions::IllegalVectorSizeException::IllegalVectorSizeException()
{

}

const char * exceptions::IllegalVectorSizeException::what() const {
	return (string("One vector has length ") + std::to_string(vect1) + string(" but other length is ") + std::to_string(vect2)).c_str();
}

exceptions::IllegalVectorSizeException::IllegalVectorSizeException(int vect1, int vect2):vect1(vect1),vect2(vect2)
{

}


exceptions::IllegalVectorSizeException::~IllegalVectorSizeException()
{
}
