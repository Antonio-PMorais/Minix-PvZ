#include "peashooter.h"
#include "game_state.h"
#include "board.h"
#include "projectile.h"
#include "zombie.h"
#include "v_card.h"
#include <stdio.h>
#include "sprites/peashooter.xpm"

#define MAX_PEASHOOTERS 45

typedef struct {
    bool active;
    int row, col;
    int16_t hp;
    uint16_t shoot_timer;
} peashooter_t;

static peashooter_t peashooters[MAX_PEASHOOTERS];
static xpm_image_t peashooter_img;
static uint8_t *peashooter_pixmap = NULL;

void peashooters_init() {
    for (int i = 0; i < MAX_PEASHOOTERS; i++) peashooters[i].active = false;
    peashooter_pixmap = xpm_load((xpm_map_t) peashooter_xpm, XPM_8_8_8_8, &peashooter_img);
}

bool peashooters_spawn(int row, int col) {
    for (int i = 0; i < MAX_PEASHOOTERS; i++) {
        if (!peashooters[i].active) {
            peashooters[i].active = true;
            peashooters[i].row = row;
            peashooters[i].col = col;
            peashooters[i].hp = 300;
            peashooters[i].shoot_timer = 0;
            return true;
        }
    }
    return false;
}

void peashooters_update() {
    for (int i = 0; i < MAX_PEASHOOTERS; i++) {
        if (!peashooters[i].active) continue;

        peashooters[i].shoot_timer++;

        // shoot if zombie in front
        if (peashooters[i].shoot_timer >= 84) {
            peashooters[i].shoot_timer = 0;

            int plant_x = GRID_START_X + peashooters[i].col * CELL_W;
            if (zombie_in_lane_ahead(peashooters[i].row, plant_x)) {
                int px = plant_x + CELL_W;
                int py = GRID_START_Y + peashooters[i].row * CELL_H + CELL_H / 2 - 15;
                spawn_projectile(peashooters[i].row, px, py);
            }
        }
    }
}

void peashooters_render() {
    if (peashooter_pixmap == NULL) return;
    for (int i = 0; i < MAX_PEASHOOTERS; i++) {
        if (!peashooters[i].active) continue;
        int cell_x = GRID_START_X + peashooters[i].col * CELL_W;
        int cell_y = GRID_START_Y + peashooters[i].row * CELL_H;
        int draw_x = cell_x + (CELL_W - peashooter_img.width) / 2;
        int draw_y = cell_y + (CELL_H - peashooter_img.height) / 2;
        vg_draw_xpm(peashooter_img, peashooter_pixmap, draw_x, draw_y);
    }
}

void peashooters_take_damage(int row, int col, int damage) {
    for (int i = 0; i < MAX_PEASHOOTERS; i++) {
        if (peashooters[i].active && peashooters[i].row == row && peashooters[i].col == col) {
            peashooters[i].hp -= damage;
            if (peashooters[i].hp <= 0) {
                peashooters[i].active = false;
                board_clear_cell(row, col);
            }
            return;
        }
    }
}
