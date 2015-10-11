#include "alistint.h"
#include <cstdlib>


AListInt::AListInt() :
	_size(0), _cap(5)	
{ // cap = 5
	_data = new int[5];
	//_size = 0;
	//_cap = 5;
}

AListInt::AListInt(int cap) :
	_size(0), _cap(cap)
{ // starting cap = cap
	_data = new int[cap];
	//_size = 0;
	//_cap = cap;
}

AListInt::AListInt(const AListInt& other) { // copy constructor
	_data = new int[other.size()];
	_size = other.size();
	_cap = other.size();
	
	for(unsigned int i = 0; i < _size; i++) {
		_data[i] = other.get(i);
	}
	
	return;
}

AListInt& AListInt::operator=(const AListInt& other) { // assignment operator
	if( this == &other) {
		return *this;
	}
	if (_data) {
	delete [] _data;
	}
	
	_size = other.size();
	_cap = _size;
	_data = new int[_size];
	
	for(unsigned int i = 0; i < _size; i++) {
		_data[i] = other.get(i);
	}
	
	return *this;
}

AListInt::~AListInt() { // destructor
	delete [] _data;
}

int AListInt::size() const { // returns _size
	return _size;
}

bool AListInt::empty() const { // returns true if empty
	if( _size == 0) {
		return true;
	} else {
		return false;
	}
}

void AListInt::insert (int pos, const int& val) { // inserts val into position pos
	if( pos < 0 || pos > _size) {
		return;
	}

	if( _cap <= _size ) {
		resize();	
	}
	
	for(unsigned int i = _size; i > pos; i--) {
		_data[i] = _data[i-1];
	}
	_data[pos] = val;
	
	_size++;
	return;
}

void AListInt::remove (int pos) { // Removes from position pos
	if( pos < 0 || pos >= _size) {
		return;
	}

	for(unsigned int i = pos; i < _size; i++) {
		_data[i] = _data[i+1];
	}
	
	_size--;
	return;
}

void AListInt::set (int position, const int& val) { // overwrites position position with val
	if( position < 0 || position >= _size) {
		return;
	}

	_data[position] = val;
	return;
}

int& AListInt::get (int position) { //Returns value at index pos
	if( empty() ) {
		int x = -5;
		return x;
	}
	if( position < 0 || position >= _size) {
		return _data[0];
	}

	return _data[position];
}

int const & AListInt::get (int position) const { // Returns const value at index pos
	if( position < 0 || position >= _size) {
		int x = -1
		return x;
	}

	return _data[position];
}

AListInt AListInt::operator+(const AListInt& other) const { // + array lists
	AListInt newAList(_size + other.size() );
	for(int i = 0; i < newAList.size(); i++) {
		if( i < _size) {
			newAList[i] = _data[i];
		} else {
			newAList[i] = other.get(i-_size);
		}
	}
	return newAList;
}

 int const & AListInt::operator[](int position) const { // [] notation for getting items
 	return _data[position]; 
 }

int& AListInt::operator[](int position) { // not const []
	return _data[position];
}

void AListInt::resize() { // doubles _cap
	int* newArray = new int[_cap*2];
	for(unsigned int i = 0; i < _size; i++) {
		newArray[i] = _data[i];
	}
	delete [] _data;
	_cap *= 2;
	_data = newArray;
}