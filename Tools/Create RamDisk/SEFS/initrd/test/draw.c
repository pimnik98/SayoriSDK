#include <env.h>
#include <draw.h>

env_t my_env = {};

void memset(void* ptr, size_t value, size_t size) {
  size_t* b_ptr = (size_t*)ptr;
  int i = 0;

  for (i = 0; i < size; i++)
    b_ptr[i] = value;
}

int main() {
    clear_screen();

    env_io(0, &my_env);

    debug_io(2, &my_env);

    debug_io(0, my_env.OS_VERSION_MAJOR);
    debug_io(0, my_env.OS_VERSION_MINOR);
    debug_io(0, my_env.OS_VERSION_PATCH);

    debug_io(0, my_env.Display_W);
    debug_io(0, my_env.Display_H);

    /*draw_filled_rectangle(
        (my_env.Display_W - 300)/2,
        (my_env.Display_H - 100)/2,
        300,
        100,
        0xFF0000
    );
    
    screen_update();
	*/
	
    return 0;
}
