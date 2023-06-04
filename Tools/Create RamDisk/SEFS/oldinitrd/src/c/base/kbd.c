#include <base.h>
#include <stdint.h>

int kbd_getc() {
    int code = 0;

	_syscall(0x07, 0, &code, 0);

	return code;
}
