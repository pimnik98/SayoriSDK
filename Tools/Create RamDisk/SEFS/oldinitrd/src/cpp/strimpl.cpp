#include "strimpl.hpp"

char* MyString::c_str() {
	return this->str;
}

size_t MyString::size() {
	return strlen(this->str);
}

size_t MyString::length() {
	return strlen(this->str);
}

void MyString::resize(size_t n) {
	this->str = (char*)realloc(this->str, n);
}

