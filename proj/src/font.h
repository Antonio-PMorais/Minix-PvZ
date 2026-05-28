#ifndef __FONT_H
#define __FONT_H

#include <stdint.h>

// draw a single character at (x,y) with given color
void font_draw_char(char c, int x, int y, uint32_t color);

// draw a null terminated string at (x,y)
void font_draw_string(const char *str, int x, int y, uint32_t color);

// draw an integer number at (x,y)
void font_draw_number(int num, int x, int y, uint32_t color);

#endif
