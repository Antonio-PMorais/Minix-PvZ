#ifndef __GAME_STATE_H
#define __GAME_STATE_H

#include <stdint.h>
#include <stdbool.h>

// shared variables
extern int suns_count;
extern int score;
extern int current_level;
extern bool frozen;
extern uint32_t timer_counter;

// grid macros
#define GRID_START_X 0
#define GRID_START_Y 100
#define GRID_COLS    9
#define GRID_ROWS    5
#define CELL_W       89
#define CELL_H       100

#endif
