#include "stdafx.h"
#include "ByteVector.h"
#include "IllegalVectorSizeException.h"
using namespace exceptions;

ByteVector::ByteVector(int size):size(size) {
	this->word = new byte[size];
	for (size_t i = 0; i < size; i++)
	{
		this->setByte(i, 0);
	}
}

byte ByteVector::getByte(int id) const{
	return word[id];
}

void ByteVector::setByte(int id, byte value)
{
	word[id] = value;
}

ByteVector ByteVector::offestRight(int offsetsize) const {
	ByteVector returnedvect = ByteVector(this->getLen());
	for (int i = 0; i < size; i++)
	{

		if (offsetsize + i >= size || offsetsize + i < 0)
		{
			returnedvect.setByte(i, 0);
		}
		else
		{
			returnedvect.setByte(i,this->getByte(i + offsetsize));
		}
	}
	return returnedvect;
}

ByteVector ByteVector::offestLeft(int offsetsize) const { return offestRight(-offsetsize); }


ByteVector ByteVector::operator=(const ByteVector& vect) {
	if (this->getLen() != vect.getLen())throw IllegalVectorSizeException(vect.getLen(),this->getLen());
	for (size_t i = 0; i < getLen(); i++)
	{
		setByte(i, vect.getByte(i));
	}
	return vect;
}

bool ByteVector::operator<(const ByteVector & other) const {
	if (getLen() != other.getLen())throw IllegalVectorSizeException(getLen(), other.getLen());
	for (int i = 0; i < getLen(); i++)
	{
		//Индексы надо считать справа
		int index = getLen() - i - 1;
		//Если хотя бы один индекс не равен то если у этого объекта 0, то он меньше
		if (getByte(index) != other.getByte(index))return !getByte(index);
	}
	return false;
}

bool ByteVector::operator==(const ByteVector & other) const
{
	if (getLen() != other.getLen())throw 1;
	for (int i = 0; i < getLen(); i++)
	{

		if (getByte(i) != other.getByte(i))return false;
	}
	return true;
}

ByteVector ByteVector::SymmetrycSumm(const ByteVector & vect) const {
	if (this->getLen() != vect.getLen())throw IllegalVectorSizeException(this->getLen(), vect.getLen());
	ByteVector returnedvect = ByteVector(this->getLen());
	for (size_t i = 0; i < size; i++)
	{
		returnedvect.setByte(i, this->getByte(i) ^ vect.getByte(i));
	}
	return returnedvect;
}

 ByteVector::ByteVector(int vect,int size) :ByteVector(size) {
	for (size_t i = 0; i < size; i++)
	{
		this->setByte(i,((1 << i)&vect) != 0);
	}
}

//Конструктор копирования

ByteVector::ByteVector(const ByteVector & vect) :ByteVector(vect.getLen()) {

	for (size_t i = 0; i < size; i++)
	{
		this->setByte(i, vect.getByte(i));
	}

}

ByteVector::~ByteVector() {
	delete[] word;
}


ostream& operator<<(ostream& a, const ByteVector&vect) {
	for (int i = vect.size - 1; i >= 0; i--)
	{
		a << vect.getByte(i);
	}
	return a;
}