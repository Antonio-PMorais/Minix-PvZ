#include "sunflower.h"
#include "game_state.h"
#include "board.h"
#include "sun.h"
#include "v_card.h"
#include <stdio.h>
#include <stdlib.h>
#include "sprites/sunflower.xpm"

#define MAX_SUNFLOWERS 45

typedef struct {
    bool active;
    int row, col;
    int16_t hp;
    uint16_t sun_timer;
} sunflower_t;

static sunflower_t sunflowers[MAX_SUNFLOWERS];
static xpm_image_t sunflower_img;
static uint8_t *sunflower_pixmap = NULL;

void sunflowers_init() {
    for (int i = 0; i < MAX_SUNFLOWERS; i++) sunflowers[i].active = false;
    sunflower_pixmap = xpm_load((xpm_map_t) sunflower_xpm, XPM_8_8_8_8, &sunflower_img);
}

bool sunflowers_spawn(int row, int col) {
    for (int i = 0; i < MAX_SUNFLOWERS; i++) {
        if (!sunflowers[i].active) {
            sunflowers[i].active = true;
            sunflowers[i].row = row;
            sunflowers[i].col = col;
            sunflowers[i].hp = 300;
            sunflowers[i].sun_timer = 0;
            return true;
        }
    }
    return false;
}

void sunflowers_update() {
    for (int i = 0; i < MAX_SUNFLOWERS; i++) {
        if (!sunflowers[i].active) continue;

        sunflowers[i].sun_timer++;
        if (sunflowers[i].sun_timer >= 840) {
            sunflowers[i].sun_timer = 0;
            int sx = GRID_START_X + sunflowers[i].col * CELL_W + 20 + (rand() % 40);
            int sy = GRID_START_Y + sunflowers[i].row * CELL_H + 20 + (rand() % 40);
            spawn_sun(sx, sy, sy);
        }
    }
}

void sunflowers_render() {
    if (sunflower_pixmap == NULL) return;
    for (int i = 0; i < MAX_SUNFLOWERS; i++) {
        if (!sunflowers[i].active) continue;
        int cell_x = GRID_START_X + sunflowers[i].col * CELL_W;
        int cell_y = GRID_START_Y + sunflowers[i].row * CELL_H;
        int draw_x = cell_x + (CELL_W - sunflower_img.width) / 2;
        int draw_y = cell_y + (CELL_H - sunflower_img.height) / 2;
        vg_draw_xpm(sunflower_img, sunflower_pixmap, draw_x, draw_y);
    }
}

void sunflowers_take_damage(int row, int col, int damage) {
    for (int i = 0; i < MAX_SUNFLOWERS; i++) {
        if (sunflowers[i].active && sunflowers[i].row == row && sunflowers[i].col == col) {
            sunflowers[i].hp -= damage;
            if (sunflowers[i].hp <= 0) {
                sunflowers[i].active = false;
                board_clear_cell(row, col);
            }
            return;
        }
    }
}
