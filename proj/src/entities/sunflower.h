#ifndef __SUNFLOWER_H
#define __SUNFLOWER_H

#include <stdbool.h>

void sunflowers_init();
bool sunflowers_spawn(int row, int col);
void sunflowers_update();
void sunflowers_render();
void sunflowers_take_damage(int row, int col, int damage);

#endif
