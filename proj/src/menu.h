#ifndef __MENU_H
#define __MENU_H

#include <stdint.h>
#include <stdbool.h>
#include <lcom/lcf.h>

void menu_init();
void menu_render(int mouse_x, int mouse_y);
void menu_on_mouse(struct packet *pp, int mouse_x, int mouse_y);
void menu_on_key(uint8_t scancode);

#endif
