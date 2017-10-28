#pragma once
#include <iostream>
using namespace std;
typedef bool byte;

class ByteVector
{
private:
	//Все хранится наоборот
	byte* word;
	const int size;
	
public:
	ByteVector(int size);
	int getLen() const { return size; }
	byte getByte(int id)  const;
	void setByte(int id, byte value);
	ByteVector offestRight(int offsetsize) const;
	ByteVector offestLeft(int offsetsize) const;
	ByteVector SymmetrycSumm(const ByteVector&vect) const;
	//ByteVector() :ByteVector(0, 0) {}

	ByteVector(int vect,int size);
	//Конструктор копирования
	ByteVector(const ByteVector& vect);
	ByteVector operator=(const ByteVector& vect);
	bool operator<(const ByteVector& other)const;
	bool operator==(const ByteVector& other)const;
	~ByteVector();
	friend ostream& operator<<(ostream& a, const ByteVector&vect);
};

