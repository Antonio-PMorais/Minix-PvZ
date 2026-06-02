#ifndef __ENTITIES_H
#define __ENTITIES_H

#include <stdint.h>
#include <stdbool.h>
#include <lcom/lcf.h>

extern xpm_image_t sunflower_img;
extern uint8_t *sunflower_pixmap;

extern xpm_image_t sun_img;
extern uint8_t *sun_pixmap;

extern xpm_image_t peashooter_projectile_img;
extern uint8_t *peashooter_projectile_pixmap;

extern xpm_image_t zombie_default_img;
extern uint8_t *zombie_default_pixmap;

// max counts
#define MAX_ZOMBIES      20
#define MAX_PROJECTILES  30
#define MAX_SUNS         10

// zombie
typedef struct {
    bool active;
    int16_t x;
    uint8_t lane;       // row 0-4
    int16_t hp;
    int16_t speed;
    bool eating;
    uint16_t eat_timer;
} zombie_t;

// projectile (pea)
typedef struct {
    bool active;
    int16_t x, y;
    uint8_t lane;
    int16_t damage;
} projectile_t;

// falling sun
typedef struct {
    bool active;
    int16_t x, y;
    int16_t target_y;
    uint16_t lifetime;
} sun_t;

// plant data per cell
typedef struct {
    int type;           // 0=none, 1=sunflower, 2=peashooter
    int16_t hp;
    uint16_t shoot_timer;
    uint16_t sun_timer;
} plant_cell_t;

// global entity arrays — defined in entities.c
extern zombie_t zombies[MAX_ZOMBIES];
extern projectile_t projectiles[MAX_PROJECTILES];
extern sun_t suns_array[MAX_SUNS];

void entities_init();

// spawn
void spawn_zombie(uint8_t lane, int level);
void spawn_projectile(uint8_t lane, int16_t x, int16_t y);
void spawn_sun(int16_t x, int16_t start_y, int16_t target_y);

// update — returns true if game over (zombie reached left edge)
bool entities_update(plant_cell_t grid[5][9], int *suns_count, int *score,
                     int level, bool frozen, uint32_t timer_counter);

// render
void entities_render(int grid_x, int grid_y, int cell_w, int cell_h, bool frozen);

// check if mouse clicked a sun, returns true if collected
bool entities_collect_sun(int16_t mx, int16_t my, int *suns_count);

// count active zombies
int entities_zombies_alive();

#endif
