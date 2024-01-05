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
    env_io(0, &my_env);

	for(int i = 0; i < 50; i++) {
	    clear_screen();
	    draw_rectangle(
    	    (my_env.Display_W - (300+(i*4)))/2,
        	(my_env.Display_H - (100+(i*4)))/2,
	        300+(i*4),
    	    100+(i*4),
        	0xBBBBBB
    	);
    
    	screen_update();
	}
		
    return 0;
}
