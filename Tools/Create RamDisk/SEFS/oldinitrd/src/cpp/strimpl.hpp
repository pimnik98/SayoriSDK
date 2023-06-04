#pragma once
#include "stdint.h"
#include "string.h"
#include "stdlib.h"

class MyString {
	public:
		MyString(const char* string) {
			this->str = (char*)calloc(strlen(string)+1, 1);
			memcpy(this->str, string, strlen(string));
		}

		~MyString() {
			free(this->str);
		}

		MyString& operator+(MyString concat) {
			size_t origlen = strlen(this->c_str());
			size_t len = strlen(concat.c_str());

			this->str = (char*)realloc(this->str, origlen+len);

			memcpy(this->str+origlen, concat.c_str(), len);
			return *this;
		}
		
		char* c_str();
		size_t size();
		size_t length();
		void resize(size_t n);
	private:
		char* str = {};
};
