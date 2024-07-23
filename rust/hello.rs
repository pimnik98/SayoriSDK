#![no_std]
#![no_main]

use core::panic::PanicInfo;
use allocator;

#[no_mangle]
fn _start() {
	main();
}

extern { fn printf(text: &[u8]); }

struct CL {
    elem: [u8; 256],
    ta: Box<CL>
}

fn main() {
	unsafe {
		printf(b"Hello!\n");
	}
}

#[panic_handler]
fn _panic_handler(info: &PanicInfo) -> ! {
	loop {}	
}
