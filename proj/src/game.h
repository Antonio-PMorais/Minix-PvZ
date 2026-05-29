#ifndef __GAME_H
#define __GAME_H

#include <stdint.h>
#include <stdbool.h>
#include <lcom/lcf.h>

typedef enum {
    MAIN_MENU,
    PLAYING,
    LEVEL_COMPLETE
} GameState;

void game_init();
void game_update();
void game_render();
bool game_should_quit();

void game_on_key(uint8_t scancode);
void game_on_mouse(struct packet *pp);

void game_change_state(GameState new_state);
void game_set_quit();

#endif

