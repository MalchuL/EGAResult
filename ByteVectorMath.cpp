#include "stdafx.h"
#include "ByteVectorMath.h"
#include "IllegalVectorSizeException.h"
using namespace exceptions;

int ByteVectorMath::HemmingLength(ByteVector & vect1, ByteVector & vect2)  {
	if (vect1.getLen() != vect2.getLen())throw IllegalVectorSizeException(vect1.getLen(), vect1.getLen());
	int size = vect1.getLen();
	int length = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (vect1.getByte(i) != vect2.getByte(i))length++;
	}
	return length;

}
