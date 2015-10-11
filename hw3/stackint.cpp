#include "stackint.h"
#include <cstdlib>

StackInt::StackInt() {
	
}

StackInt::~StackInt() {
	
}

bool StackInt::empty() const {
	if(list_.AListInt::empty()) {
		return true;
	} else {
		return false;
	}
}

void StackInt::push(const int& val) {
	list_.insert(list_.AListInt::size(), val);
	return;
}

int const &  StackInt::top() const {
	return list_.get(list_.AListInt::size() - 1);
}

void StackInt::pop() {
	list_.remove(list_.AListInt::size()-1);
	return;
}