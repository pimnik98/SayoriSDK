#include <base.h>

int main() {
	char* data;

	data[0] = 'H';
	data[1] = 'y';
	data[2] = 'v';
	data[3] = 'a';
	data[4] = 'a';

	debug_io(1, "Address of alloc (no): ");
	debug_io(2, data);

	debug_io(1, data);
	
	_syscall(6, 0, data, 32); // Alloc
	
	debug_io(1, "Address of alloc: ");
	debug_io(2, data);

	_syscall(6, 1, data, 0);  // Free

	
	return 0;
}
