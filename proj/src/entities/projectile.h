#ifndef __PROJECTILE_H
#define __PROJECTILE_H

#include <stdint.h>
#include <stdbool.h>

void projectiles_init();
void spawn_projectile(uint8_t lane, int16_t x, int16_t y);
void projectiles_update();
void projectiles_render();

#endif
