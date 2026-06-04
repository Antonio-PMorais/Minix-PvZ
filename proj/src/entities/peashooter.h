#ifndef __PEASHOOTER_H
#define __PEASHOOTER_H

#include <stdbool.h>

void peashooters_init();
bool peashooters_spawn(int row, int col);
void peashooters_update();
void peashooters_render();
void peashooters_take_damage(int row, int col, int damage);

#endif
