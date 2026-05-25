#ifndef __GAME_H
#define __GAME_H

#include <stdint.h>
#include <stdbool.h>
#include <lcom/lcf.h>

void game_init();
void game_update();
void game_render();
bool game_should_quit();

void game_on_key(uint8_t scancode);
void game_on_mouse(struct packet *pp);

#endif

