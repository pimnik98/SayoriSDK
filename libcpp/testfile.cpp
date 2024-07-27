#include "fstream"

extern "C" {
	#include "../libc/include/printf.h"
}

int main() {
	//printf("Hello world!\n");
	std::string filename = "Pokemon.txt";
#ifdef SAYORIOS
	filename = "T:\\Pokemon.txt";
	//#error "Compiling for SAYORIOS"
#endif
	std::fstream stream(filename, std::ios::out);
	std::string pokemon = "Zeraora!\n";

	stream.write(pokemon.c_str(), pokemon.length());

	printf("String is: %s\n", filename.c_str());
	return 0;
}
