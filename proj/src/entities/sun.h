#ifndef __SUN_H
#define __SUN_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_SUNS 10

typedef struct {
    bool active;
    int16_t x, y;
    int16_t target_y;
    uint16_t lifetime;
} sun_t;

void suns_init();
void spawn_sun(int16_t x, int16_t start_y, int16_t target_y);
void suns_update();
void suns_render();
bool suns_check_click(int16_t mx, int16_t my);

#endif
