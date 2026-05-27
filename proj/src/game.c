#include "game.h"
#include "menu.h"
#include "v_card.h"
#include "i8042.h"
#include "proj.h"
#include <stdlib.h>

// screen dimensions
#define SCREEN_W 800
#define SCREEN_H 600


#define COLOR_BG      0x228B22
#define COLOR_UI      0x3b4d24
#define COLOR_CELL    0x32CD32
#define COLOR_PLANT   0x00FF00
#define COLOR_CURSOR  0xFFFFFF

static GameState current_state = MAIN_MENU;

#define GRID_COLS 9
#define GRID_ROWS 5
#define CELL_SIZE 80
#define GRID_START_X 40
#define GRID_START_Y 150

// mouse state
static int16_t mouse_x, mouse_y;
static bool prev_lb = false; // store if left btn was pressed in last frame
#define CURSOR_SIZE 8

static int grid[GRID_ROWS][GRID_COLS];

static bool quit = false;
#define ESC_BREAKCODE 0x81

void game_change_state(GameState new_state) {
    current_state = new_state;
}

void game_set_quit() {
    quit = true;
}

void game_init() {
    // start mouse in center
    mouse_x = SCREEN_W / 2;
    mouse_y = SCREEN_H / 2;
    
    for (int r = 0; r < GRID_ROWS; r++) {
        for (int c = 0; c < GRID_COLS; c++) {
            grid[r][c] = 0;
        }
    }
}

void game_update() {

}

void game_render() {
    if (current_state == MAIN_MENU) {
        menu_render(mouse_x, mouse_y);
    }
    else if (current_state == PLAYING) {
        vg_clear(COLOR_BG);

        vg_draw_rectangle(0, 0, SCREEN_W, 100, COLOR_UI);

        // draw grid
        for (int r = 0; r < GRID_ROWS; r++) {
            for (int c = 0; c < GRID_COLS; c++) {
                int cell_x = GRID_START_X + c * CELL_SIZE;
                int cell_y = GRID_START_Y + r * CELL_SIZE;

                vg_draw_rectangle(cell_x + 2, cell_y + 2, CELL_SIZE - 4, CELL_SIZE - 4, COLOR_CELL);

                if (grid[r][c] == 1) {
                    vg_draw_rectangle(cell_x + 20, cell_y + 20, 40, 40, COLOR_PLANT);
                }
            }
        }
    }

    // draw mouse
        vg_draw_rectangle(mouse_x - CURSOR_SIZE / 2, mouse_y - 1, CURSOR_SIZE, 2, COLOR_CURSOR);
        vg_draw_rectangle(mouse_x - 1, mouse_y - CURSOR_SIZE / 2, 2, CURSOR_SIZE, COLOR_CURSOR);

        vg_flip();
}

bool game_should_quit() {
    return quit;
}

void game_on_key(uint8_t scancode) {
    if (current_state == MAIN_MENU) {
        menu_on_key(scancode);
    } else if (current_state == PLAYING) {
        if (scancode == ESC_BREAKCODE) {
            current_state = MAIN_MENU; 
        }
    }
}

void game_on_mouse(struct packet *pp) {
    // update mouse
    mouse_x += pp->delta_x;
    mouse_y -= pp->delta_y;

    // mouse limits
    if (mouse_x < 0) mouse_x = 0;
    if (mouse_x >= SCREEN_W) mouse_x = SCREEN_W - 1;
    if (mouse_y < 0) mouse_y = 0;
    if (mouse_y >= SCREEN_H) mouse_y = SCREEN_H - 1;

    //handle click
    if (current_state == MAIN_MENU) {
        menu_on_mouse(pp, mouse_x, mouse_y);
    } 
    else if (current_state == PLAYING) {
        if (pp->lb && !prev_lb) {
            
            if (mouse_x >= GRID_START_X && mouse_x < GRID_START_X + GRID_COLS * CELL_SIZE &&
                mouse_y >= GRID_START_Y && mouse_y < GRID_START_Y + GRID_ROWS * CELL_SIZE) {
                
                int col = (mouse_x - GRID_START_X) / CELL_SIZE;
                int row = (mouse_y - GRID_START_Y) / CELL_SIZE;

                if (grid[row][col] == 0) {
                    grid[row][col] = 1;
                }
            }
        }
        prev_lb = pp->lb;
    }
    
    prev_lb = pp->lb;
}
