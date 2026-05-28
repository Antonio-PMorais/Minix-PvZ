#include "menu.h"
#include "v_card.h"
#include "game.h"

//button coordinates
#define BTN_W 200
#define BTN_H 80
#define BTN_PLAY_X 300
#define BTN_PLAY_Y 200
#define BTN_EXIT_X 300
#define BTN_EXIT_Y 320

static bool prev_lb = false;

void menu_init() {
    prev_lb = false;
}

void menu_render(int mouse_x, int mouse_y) {
    vg_clear(0x111111);

    uint32_t play_color = 0x005500;
    uint32_t exit_color = 0x550000;

    // detect hover
    if (mouse_x >= BTN_PLAY_X && mouse_x <= BTN_PLAY_X + BTN_W && 
        mouse_y >= BTN_PLAY_Y && mouse_y <= BTN_PLAY_Y + BTN_H) {
        play_color = 0x00FF00;
    }

    if (mouse_x >= BTN_EXIT_X && mouse_x <= BTN_EXIT_X + BTN_W && 
        mouse_y >= BTN_EXIT_Y && mouse_y <= BTN_EXIT_Y + BTN_H) {
        exit_color = 0xFF0000;
    }

    // draw buttons
    vg_draw_rectangle(BTN_PLAY_X, BTN_PLAY_Y, BTN_W, BTN_H, play_color);
    vg_draw_rectangle(BTN_EXIT_X, BTN_EXIT_Y, BTN_W, BTN_H, exit_color);
}

void menu_on_mouse(struct packet *pp, int mouse_x, int mouse_y) {
    // handle click
    if (pp->lb && !prev_lb) {
        
        if (mouse_x >= BTN_PLAY_X && mouse_x <= BTN_PLAY_X + BTN_W && 
            mouse_y >= BTN_PLAY_Y && mouse_y <= BTN_PLAY_Y + BTN_H) {

            game_init();
            game_change_state(PLAYING);
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
