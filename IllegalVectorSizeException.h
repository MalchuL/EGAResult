#pragma once
#include "vcruntime_exception.h"
#include "ByteVector.h"
#include <string>
namespace exceptions {
	class IllegalVectorSizeException :
		public std::exception
	{
	private:
		IllegalVectorSizeException();
		int vect1, vect2;
	public:
		const char* what() const;
		
		IllegalVectorSizeException(int vectSize1,int vectSize2);
		~IllegalVectorSizeException();
	};

}