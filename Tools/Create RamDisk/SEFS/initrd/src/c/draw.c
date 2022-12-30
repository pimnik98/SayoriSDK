#include <env.h>
#include <draw.h>

env_t my_env;

void memset(void* ptr, size_t value, size_t size) {
  size_t* b_ptr = (size_t*)ptr;
  int i = 0;

  for (i = 0; i < size; i++)
    b_ptr[i] = value;
}

int main() {
	draw_init();
    clear_screen();

    env_io(0, &my_env);

    // debug_io(2, &my_env); // Log addres of struct

    // debug_io(0, my_env.OS_VERSION_MAJOR);
    // debug_io(0, my_env.OS_VERSION_MINOR);
    // debug_io(0, my_env.OS_VERSION_PATCH);

    // debug_io(0, my_env.Display_W);
    // debug_io(0, my_env.Display_H);

    draw_rectangle(
        (my_env.Display_W - 300)/2,
        (my_env.Display_H - 100)/2,
        300,
        100,
        0xBBBBBB
    );
    
    screen_update();
		
    return 0;
}
