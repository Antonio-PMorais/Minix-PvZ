#include "menu.h"
#include "v_card.h"
#include "game.h"
#include "font.h"

//button coordinates
#define BTN_W 200
#define BTN_H 60
#define BTN_PLAY_X 300
#define BTN_PLAY_Y 160
#define BTN_LEVELS_X 300
#define BTN_LEVELS_Y 250
#define BTN_EXIT_X 300
#define BTN_EXIT_Y 340

static bool prev_lb = false;

void menu_init() {
    prev_lb = false;
}

void menu_render(int mouse_x, int mouse_y) {
    vg_clear(0x111111);

    uint32_t play_color = 0x005500;
    uint32_t levels_color = 0x555500;
    uint32_t exit_color = 0x550000;

    // detect hover
    if (mouse_x >= BTN_PLAY_X && mouse_x <= BTN_PLAY_X + BTN_W && 
        mouse_y >= BTN_PLAY_Y && mouse_y <= BTN_PLAY_Y + BTN_H) {
        play_color = 0x00FF00;
    }

    if (mouse_x >= BTN_LEVELS_X && mouse_x <= BTN_LEVELS_X + BTN_W && 
        mouse_y >= BTN_LEVELS_Y && mouse_y <= BTN_LEVELS_Y + BTN_H) {
        levels_color = 0xFFFF00;
    }

    if (mouse_x >= BTN_EXIT_X && mouse_x <= BTN_EXIT_X + BTN_W && 
        mouse_y >= BTN_EXIT_Y && mouse_y <= BTN_EXIT_Y + BTN_H) {
        exit_color = 0xFF0000;
    }

    // draw buttons
    vg_draw_rectangle(BTN_PLAY_X, BTN_PLAY_Y, BTN_W, BTN_H, play_color);
    vg_draw_rectangle(BTN_LEVELS_X, BTN_LEVELS_Y, BTN_W, BTN_H, levels_color);
    vg_draw_rectangle(BTN_EXIT_X, BTN_EXIT_Y, BTN_W, BTN_H, exit_color);

    font_draw_string("PLAY", BTN_PLAY_X + 76, BTN_PLAY_Y + 23, 0xFFFFFF);
    font_draw_string("LEVELS", BTN_LEVELS_X + 64, BTN_LEVELS_Y + 23, 0xFFFFFF);
    font_draw_string("EXIT", BTN_EXIT_X + 76, BTN_EXIT_Y + 23, 0xFFFFFF);
}

void menu_on_mouse(struct packet *pp, int mouse_x, int mouse_y) {
    // handle click
    if (pp->lb && !prev_lb) {
        
        if (mouse_x >= BTN_PLAY_X && mouse_x <= BTN_PLAY_X + BTN_W && 
            mouse_y >= BTN_PLAY_Y && mouse_y <= BTN_PLAY_Y + BTN_H) {

            game_init_level(1);
            game_change_state(PLAYING);
        }

        if (mouse_x >= BTN_LEVELS_X && mouse_x <= BTN_LEVELS_X + BTN_W && 
            mouse_y >= BTN_LEVELS_Y && mouse_y <= BTN_LEVELS_Y + BTN_H) {
            game_change_state(LEVEL_SELECT);
        }

        if (mouse_x >= BTN_EXIT_X && mouse_x <= BTN_EXIT_X + BTN_W && 
            mouse_y >= BTN_EXIT_Y && mouse_y <= BTN_EXIT_Y + BTN_H) {
            game_set_quit();
        }
    }
    prev_lb = pp->lb;
}

void menu_on_key(uint8_t scancode) {
    // press esc
    if (scancode == 0x81) {
        game_set_quit();
    }
}
