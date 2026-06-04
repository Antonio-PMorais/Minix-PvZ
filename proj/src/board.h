#ifndef __BOARD_H
#define __BOARD_H

#include <stdbool.h>
#include <stdint.h>

typedef enum { 
    PLANT_NONE = 0, 
    PLANT_SUNFLOWER = 1, 
    PLANT_PEASHOOTER = 2 
} plant_type_t;

void board_init();
bool board_is_empty(int row, int col);
bool board_place_plant(int row, int col, plant_type_t type);
void board_take_damage(int row, int col, int damage);
plant_type_t board_get_plant_type(int row, int col);
void board_clear_cell(int row, int col);

#endif
