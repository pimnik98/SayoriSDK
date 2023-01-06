#pragma once

#include "stdint.h"

typedef struct rgb_struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color;

typedef struct screen_pixel {
    rgb_color color;
    uint32_t x, y;
} screen_pixel;

#define PACK_INTO_RGB(struct_px) ((struct_px.r & 0xff) << 16)  |\
                                 ((struct_px.g & 0xff) << 8) |\
                                  (struct_px.b & 0xff)

void _draw_pixel(size_t x, size_t y, rgb_color color);
void draw_pixel(size_t x, size_t y, uint32_t color);
void fill_screen(uint32_t color);
void clear_screen();
void draw_rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
void draw_filled_rectangle(size_t x, size_t y, size_t w, size_t h, uint32_t fill);
void screen_update();
