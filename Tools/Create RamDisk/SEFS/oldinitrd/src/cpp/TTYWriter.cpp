#include "TTYWriter.hpp"

extern "C" void atexit() {}

std::TTYWriter std::cout;
char std::endl[2] = {'\n', 0};
