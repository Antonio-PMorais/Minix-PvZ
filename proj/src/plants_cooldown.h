#ifndef __PLANTS_COOLDOWN_H
#define __PLANTS_COOLDOWN_H

#include <stdbool.h>
#include "board.h"

#define COOLDOWN_FAST       450  // 7.5s
#define COOLDOWN_SLOW       1800 // 30s
#define COOLDOWN_VERY_SLOW  3000 // 50s

void cooldowns_init();
void cooldowns_update();
bool cooldown_is_ready(plant_type_t type);
void cooldown_start(plant_type_t type);

#endif