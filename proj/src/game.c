#include "game.h"
#include "menu.h"
#include "v_card.h"
#include "i8042.h"
#include "proj.h"
#include <stdlib.h>
#include "font.h"
#include "entities.h"
#include "rtc.h"

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

// game entities and state
static plant_cell_t plant_grid[5][9];
static int suns_count = 150;
static int score = 0;
static int level = 1;
static int selected_plant = 1;  // 1=sunflower, 2=peashooter
static bool frozen = false;
static uint32_t freeze_timer = 0;

// wave spawning
static int zombies_to_spawn = 0;
static uint32_t spawn_timer = 0;
static bool wave_active = false;

// RTC
static uint32_t rtc_timer = 0;
static rtc_date current_time;
#define ESC_BREAKCODE 0x81

void game_change_state(GameState new_state) {
    current_state = new_state;
}

void game_set_quit() {
    quit = true;
}

void game_init() {
    mouse_x = SCREEN_W / 2;
    mouse_y = SCREEN_H / 2;

    for (int r = 0; r < GRID_ROWS; r++) {
        for (int c = 0; c < GRID_COLS; c++) {
            grid[r][c] = 0;
        }
    }

    entities_init();

    suns_count = 150;
    score = 0;
    level = 1;
    selected_plant = 1;
    frozen = false;
    freeze_timer = 0;
    zombies_to_spawn = 0;
    spawn_timer = 0;
    wave_active = false;
    rtc_timer = 0;

    for (int r = 0; r < GRID_ROWS; r++) {
        for (int c = 0; c < GRID_COLS; c++) {
            plant_grid[r][c].type = 0;
            plant_grid[r][c].hp = 0;
            plant_grid[r][c].shoot_timer = 0;
            plant_grid[r][c].sun_timer = 0;
        }
    }

    rtc_read_date(&current_time);

    srand(current_time.seconds + current_time.minutes * 60);
}

void game_update() {
    if (current_state == PLAYING) {
        if (frozen) {
            if (freeze_timer > 0) {
                freeze_timer--;
            }

            if (freeze_timer == 0) {
                frozen = false;
            }
        }

        if (!wave_active && entities_zombies_alive() == 0) {
            zombies_to_spawn = 3 + level * 2;
            spawn_timer = 0;
            wave_active = true;
        }

        if (wave_active && zombies_to_spawn > 0) {
            spawn_timer++;

            int interval = 300 - level * 15;
            if (interval < 120) {
                interval = 120;
            }

            if (spawn_timer >= (uint32_t) interval) {
                spawn_timer = 0;
                spawn_zombie(rand() % GRID_ROWS, level);
                zombies_to_spawn--;

                if (zombies_to_spawn == 0) {
                    wave_active = false;
                }
            }
        }

        bool game_over = entities_update(
            plant_grid,
            &suns_count,
            &score,
            level,
            frozen,
            timer_counter
        );

        if (game_over) {
            rtc_read_date(&current_time);
            current_state = MAIN_MENU;
        }

        if (!wave_active && entities_zombies_alive() == 0 && level > 0) {
            level++;
        }

        rtc_timer++;
        if (rtc_timer >= 60) {
            rtc_read_date(&current_time);
            rtc_timer = 0;
        }
    }
}

void game_render() {
    if (current_state == MAIN_MENU) {
        menu_render(mouse_x, mouse_y);
    }
    else if (current_state == PLAYING) {
        vg_clear(COLOR_BG);

        // top UI bar
        vg_draw_rectangle(0, 0, SCREEN_W, 100, COLOR_UI);

        // draw grid background
        for (int r = 0; r < GRID_ROWS; r++) {
            for (int c = 0; c < GRID_COLS; c++) {
                int cell_x = GRID_START_X + c * CELL_SIZE;
                int cell_y = GRID_START_Y + r * CELL_SIZE;

                vg_draw_rectangle(
                    cell_x + 2,
                    cell_y + 2,
                    CELL_SIZE - 4,
                    CELL_SIZE - 4,
                    COLOR_CELL
                );
            }
        }

        // draw plants
        for (int r = 0; r < GRID_ROWS; r++) {
            for (int c = 0; c < GRID_COLS; c++) {
                int cell_x = GRID_START_X + c * CELL_SIZE;
                int cell_y = GRID_START_Y + r * CELL_SIZE;

                if (plant_grid[r][c].type == 1) {
                    // sunflower
                    vg_draw_rectangle(cell_x + 20, cell_y + 15, 40, 40, 0xFFFF00);
                    vg_draw_rectangle(cell_x + 28, cell_y + 23, 24, 24, 0x8B4513);
                }
                else if (plant_grid[r][c].type == 2) {
                    // peashooter
                    vg_draw_rectangle(cell_x + 20, cell_y + 15, 40, 40, 0x00FF00);
                    vg_draw_rectangle(cell_x + 50, cell_y + 30, 12, 10, 0x228B22);
                }
            }
        }

        // draw zombies, projectiles and suns
        entities_render(GRID_START_X, GRID_START_Y, CELL_SIZE, frozen);

        // HUD
        font_draw_string("SUNS:", 10, 15, 0xFFFF00);
        font_draw_number(suns_count, 80, 15, 0xFFFF00);

        font_draw_string("SCORE:", 200, 15, 0xFFFFFF);
        font_draw_number(score, 280, 15, 0xFFFFFF);

        font_draw_string("LVL:", 400, 15, 0xFFFFFF);
        font_draw_number(level, 450, 15, 0xFFFFFF);

        //draw pant options
        uint32_t sun_color = (selected_plant == 1) ? 0xFFFF00 : 0x888888;
        uint32_t pea_color = (selected_plant == 2) ? 0x00FF00 : 0x888888;

        font_draw_string("1-SUN", 10, 60, sun_color);
        font_draw_string("2-PEA", 110, 60, pea_color);

        if (frozen) {
            font_draw_string("FROZEN", 500, 60, 0x0000FF);
        }

        // RTC time
        char ts[9];
        ts[0] = '0' + current_time.hours / 10;
        ts[1] = '0' + current_time.hours % 10;
        ts[2] = ':';
        ts[3] = '0' + current_time.minutes / 10;
        ts[4] = '0' + current_time.minutes % 10;
        ts[5] = ':';
        ts[6] = '0' + current_time.seconds / 10;
        ts[7] = '0' + current_time.seconds % 10;
        ts[8] = '\0';

        font_draw_string(ts, 680, 15, 0xFFFFFF);
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

        if (scancode == 0x02) {
            selected_plant = 1;
        }

        if (scancode == 0x03) {
            selected_plant = 2;
        }

        if (scancode == 0x39 && !frozen) {
            frozen = true;
            freeze_timer = 180;
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
            // try to collect sun first
            bool sun_collected = entities_collect_sun(mouse_x, mouse_y, &suns_count);

            // plant only if click is inside the grid
            if(!sun_collected){
                if (mouse_x >= GRID_START_X &&
                    mouse_x < GRID_START_X + GRID_COLS * CELL_SIZE &&
                    mouse_y >= GRID_START_Y &&
                    mouse_y < GRID_START_Y + GRID_ROWS * CELL_SIZE) {

                    int col = (mouse_x - GRID_START_X) / CELL_SIZE;
                    int row = (mouse_y - GRID_START_Y) / CELL_SIZE;

                    if (plant_grid[row][col].type == 0) {
                        int cost = selected_plant == 1 ? 50 : 100;

                        if (suns_count >= cost) {
                            plant_grid[row][col].type = selected_plant;
                            plant_grid[row][col].hp = 100;
                            plant_grid[row][col].shoot_timer = 0;
                            plant_grid[row][col].sun_timer = 0;
                            suns_count -= cost;
                        }
                    }
                }
            }
        }
    }

    prev_lb = pp->lb;
}
