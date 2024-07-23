use alloc::alloc::GlobalAlloc;

struct SayoriAllocator {}

unsafe extern fn malloc(size: usize) -> *mut u8;

unsafe impl GlobalAlloc for SayoriAllocator {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        
    }
}
