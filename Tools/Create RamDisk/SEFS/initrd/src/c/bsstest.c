#include <env.h>

struct a {
	char b[16];
	int c;
	short d;
	char e;
};

struct a test;

int main() {
	debug_io(1, "Address of struct: ");
	debug_io(2, &test);
	return 0;
}
