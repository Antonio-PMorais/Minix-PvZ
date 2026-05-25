#include "game.h"
#include "v_card.h"
#include "i8042.h"
#include "proj.h"

// Screen dimensions for VIDEO_MODE 0x115 (1024x768)
#define SCREEN_W 1024
#define SCREEN_H 768

// Colors (16-bit 5:6:5 packed into uint32_t)
#define COLOR_BLACK   0x0000
#define COLOR_WHITE   0xFFFF
#define COLOR_RED     0xF800
#define COLOR_GREEN   0x07E0
#define COLOR_BLUE    0x001F
#define COLOR_YELLOW  0xFFE0
#define COLOR_GRAY    0x7BEF

// Bouncing rectangle state
static int16_t rect_x, rect_y;
static int16_t rect_dx, rect_dy;
#define RECT_W 80
#define RECT_H 60

// Mouse cursor state
static int16_t mouse_x, mouse_y;
#define CURSOR_SIZE 8

// Quit flag
static bool quit = false;

void game_init() {
    // Start the rectangle in the middle moving diagonally
    rect_x = SCREEN_W / 2 - RECT_W / 2;
    rect_y = SCREEN_H / 2 - RECT_H / 2;
    rect_dx = 4;
    rect_dy = 3;

    // Start cursor in the centre
    mouse_x = SCREEN_W / 2;
    mouse_y = SCREEN_H / 2;
}

void game_update() {
    // Move rectangle and bounce off walls
    rect_x += rect_dx;
    rect_y += rect_dy;

    if (rect_x <= 0 || rect_x + RECT_W >= SCREEN_W) {
        rect_dx = -rect_dx;
        rect_x += rect_dx; // unstick from wall
    }
    if (rect_y <= 0 || rect_y + RECT_H >= SCREEN_H) {
        rect_dy = -rect_dy;
        rect_y += rect_dy;
    }
}

void game_render() {
    // 1. Clear back buffer
    vg_clear(COLOR_BLACK);

    // 2. Draw bouncing rectangle
    vg_draw_rectangle(rect_x, rect_y, RECT_W, RECT_H, COLOR_GREEN);

    // 3. Draw a simple crosshair mouse cursor
    vg_draw_rectangle(mouse_x - CURSOR_SIZE / 2, mouse_y - 1, CURSOR_SIZE, 2, COLOR_WHITE);
    vg_draw_rectangle(mouse_x - 1, mouse_y - CURSOR_SIZE / 2, 2, CURSOR_SIZE, COLOR_WHITE);

    // 4. Push back buffer to screen
    vg_flip();
}

bool game_should_quit() {
    return quit;
}

void game_on_key(uint8_t scancode) {
    if (scancode == ESC_BREAKCODE) {
        quit = true;
    }
}

void game_on_mouse(struct packet *pp) {
    // Update cursor position from mouse deltas, clamped to screen
    mouse_x += pp->delta_x;
    mouse_y -= pp->delta_y; // screen Y is inverted relative to mouse Y

    if (mouse_x < 0) mouse_x = 0;
    if (mouse_x >= SCREEN_W) mouse_x = SCREEN_W - 1;
    if (mouse_y < 0) mouse_y = 0;
    if (mouse_y >= SCREEN_H) mouse_y = SCREEN_H - 1;
}
