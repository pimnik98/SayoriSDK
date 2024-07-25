//
// Created by ndraey on 11.01.24.
//

#include "string"

extern "C" {
	#include "../../libc/include/memory.h"
	#include "../../libc/include/string.h"
}

using namespace std;

string::string()  {
    length = 0;
    string_container = (char*)calloc(1, 1);
}

string::string(const char* charptr) {
    length = strlen(charptr);
    string_container = (char*)calloc(length + 1, 1);

    memcpy(string_container, charptr, length);
}

string::~string() {
    free(string_container);
}

const char *string::c_str() const {
    return string_container;
}

void string::Append(const char* charptr) {
    auto append_length = strlen(charptr);

    string_container = (char*)realloc(string_container, length + append_length + 1);

    memcpy(string_container + length, charptr, append_length);

    length += append_length;

    string_container[length] = 0;
}

void string::Append(const string &str) {
    Append(str.c_str());
}

void string::Append(char character) {
    string_container = (char*)realloc(string_container, length + 2);

    string_container[length] = character;
    string_container[length + 1] = 0;

    length++;
}

string string::Slice(int start, int slice_length) {
    string new_string;

    // Make `start` parameter size_t?
    if(start < 0) {
        start = 0;
    }

    if(slice_length > length) {
        slice_length = length;
    } else if(slice_length == -1) {
        slice_length = (length - start);
    }

    for(int i = start; i < start + slice_length; i++) {
        new_string.Append(string_container[i]);
    }

    return new_string;
}

char * string::begin() const {
    return string_container;
}

char * string::end() const {
    return string_container + length;
}

string& string::operator=(const char* charptr) {
    free(string_container);
    length = strlen(charptr);

    string_container = (char*)calloc(length + 1, 1);
    memcpy(string_container, charptr, length);

    return *this;
}

string& string::operator+(const char* charptr) {
    this->Append(charptr);

    return *this;
}

string& string::operator+=(const char* charptr) {
    this->Append(charptr);

    return *this;
}

string& string::operator+=(const string& str) {
    this->Append(str.string_container);

    return *this;
}

char string::operator[](int index) {
    if(index < 0 || index >= length) {
    	return 0;
    }

    return string_container[index];
}

bool operator==(const char* charptr) {
	return strcmp(string_container, charptr) == 0;
}

bool operator!=(const char* charptr) {
	return strcmp(string_container, charptr) != 0;
}


/*
string::string(const string &str) {
    this->string_container = (char*)calloc(str.length + 1, 1);

    memcpy(string_container, str.string_container, str.length);

    this->length = str.length;
}
*/
