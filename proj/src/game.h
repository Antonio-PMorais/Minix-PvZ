#ifndef __GAME_H
#define __GAME_H

#include <stdint.h>
#include <stdbool.h>
#include <lcom/lcf.h>

typedef enum {
    MAIN_MENU,
    PLAYING,
    LEVEL_COMPLETE,
    LEVEL_SELECT
} GameState;

#define MAX_WAVES 50
#define MAX_ZOMBIES_PER_WAVE 50

typedef struct {
    int type; 
    int lane;
} ZombieSpawn;

typedef struct {
    int num_zombies;
    ZombieSpawn spawns[MAX_ZOMBIES_PER_WAVE];
    int time_to_next_wave; // Stored in ticks (seconds * 60)
} Wave;

extern Wave level_waves[MAX_WAVES];
extern int total_waves;
extern int current_wave;
extern int wave_timer;

void game_init();
void game_init_level(int level_number);
void game_update_waves();
void game_update();
void game_render();
bool game_should_quit();

void game_on_key(uint8_t scancode);
void game_on_mouse(struct packet *pp);

void game_change_state(GameState new_state);
void game_set_quit();

void level_select_render(int mouse_x, int mouse_y);

#endif

