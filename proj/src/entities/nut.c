#include "nut.h"
#include "board.h"
#include "sprites/walnut.xpm"
#include "game_state.h"
#include "board.h"
#include "v_card.h"


#define MAX_NUTS 45
static xpm_image_t walnut_img;
static uint8_t *walnut_pixmap = NULL;

typedef struct {
    bool active;
    int row;
    int col;
    int16_t hp;
} nut_t;

static nut_t nuts[MAX_NUTS];

void nuts_init(void) {
    for (int i = 0; i < MAX_NUTS; i++) {
        nuts[i].active = false;
        nuts[i].hp = 0;
    }
    walnut_pixmap = xpm_load((xpm_map_t) walnut_xpm, XPM_8_8_8_8, &walnut_img);
}

bool nuts_spawn(int row, int col) {
    for (int i = 0; i < MAX_NUTS; i++) {
        if (!nuts[i].active) {
            nuts[i].active = true;
            nuts[i].row = row;
            nuts[i].col = col;
            nuts[i].hp = NUT_MAX_HP;
            return true;
        }
    }
    return false;
}

void nuts_update(void) {
    for (int i = 0; i < MAX_NUTS; i++) {
        if (!nuts[i].active) continue;
    }
}

void nuts_render(void) {
    if (walnut_pixmap == NULL) return;
    for (int i = 0; i < MAX_NUTS; i++) {
        if (!nuts[i].active) continue;
        int cell_x = GRID_START_X + nuts[i].col * CELL_W;
        int cell_y = GRID_START_Y + nuts[i].row * CELL_H;
        int draw_x = cell_x + (CELL_W - walnut_img.width) / 2;
        int draw_y = cell_y + (CELL_H - walnut_img.height) / 2;
        vg_draw_xpm(walnut_img, walnut_pixmap, draw_x, draw_y);
    }
}

void nuts_take_damage(int row, int col, int damage) {
    for (int i = 0; i < MAX_NUTS; i++) {
        if (nuts[i].active && nuts[i].row == row && nuts[i].col == col) {
            nuts[i].hp -= damage;
            if (nuts[i].hp <= 0) {
                nuts[i].active = false;
                nuts[i].hp = 0;
                board_clear_cell(row, col); 
            }
            return;
        }
    }
}