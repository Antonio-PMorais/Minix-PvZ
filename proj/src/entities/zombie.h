#ifndef __ZOMBIE_H
#define __ZOMBIE_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_ZOMBIES 20

typedef struct {
    bool active;
    int16_t x;
    uint8_t lane;
    int16_t hp;
    int16_t speed;
    bool eating;
    uint16_t eat_timer;
} zombie_t;

extern zombie_t zombies[MAX_ZOMBIES];

void zombies_init();
void spawn_zombie(uint8_t lane, int level);
bool zombies_update(); 
void zombies_render();
int zombies_alive_count();
bool zombie_in_lane_ahead(uint8_t lane, int16_t plant_x);
bool zombies_check_hit(uint8_t lane, int16_t proj_x, int16_t damage);

#endif
