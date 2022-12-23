#include "draw.h"
#include "env.h"

void _draw_pixel(size_t x, size_t y, rgb_color color) {
	// FIXME: Syscall method is very slow! Use direct framebuffer instead!!!
    _syscall(0x05, 0x00, &(screen_pixel) {
        color, x, y
    });
}

void draw_pixel(size_t x, size_t y, uint32_t color) {
    uint8_t* k = (uint8_t*)&color;
    _draw_pixel(x, y, (rgb_color) {
        k[2],
        k[1],
        k[0]
    });
}

void fill_screen(uint32_t color) {
    struct env screen_data;
    env_io(0, &screen_data);

    for(int i = 0; i < screen_data.Display_H; i++) {
        for(int j = 0; j < screen_data.Display_W; j++) {
            draw_pixel(j, i, color);
        }
    }
}

void clear_screen() {
    fill_screen(0);
}

void draw_rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color) {
    debug_io(0x01, "Reached drawing function rect!!!");
    for(int i = x; i < x+w; i++) {
        draw_pixel(i, y, color);
        draw_pixel(i, y+h, color);
    }
	
    for(int j = y; j < y+h; j++) {
        draw_pixel(x, j, color);
        draw_pixel(x+w, j, color);
    }
    
}

void draw_filled_rectangle(size_t x, size_t y, size_t w, size_t h, uint32_t fill) {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            draw_pixel(x+j, y+i, fill);
        }
    }
}

void screen_update() {
    _syscall(0x05, 0x01, 0);
}
