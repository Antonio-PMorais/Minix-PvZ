#include "hud.h"
#include "font.h"
#include "v_card.h"
#include "game_state.h"

void ui_render_hud(int suns, int scr, int lvl, int selected_plant, bool is_frozen, rtc_date *time) {
    // top bar
    vg_draw_rectangle(0, 0, 800, 100, 0x3b4d24);

    // Sstats
    font_draw_string("SUNS:", 10, 15, 0xFFFF00);
    font_draw_number(suns, 80, 15, 0xFFFF00);

    font_draw_string("SCORE:", 200, 15, 0xFFFFFF);
    font_draw_number(scr, 280, 15, 0xFFFFFF);

    font_draw_string("LVL:", 400, 15, 0xFFFFFF);
    font_draw_number(lvl, 450, 15, 0xFFFFFF);

    // plants
    uint32_t sun_color = (selected_plant == 1) ? 0xFFFF00 : 0x888888;
    uint32_t pea_color = (selected_plant == 2) ? 0x00FF00 : 0x888888;

    font_draw_string("1-SUN", 10, 60, sun_color);
    font_draw_string("2-PEA", 110, 60, pea_color);

    if (is_frozen) {
        font_draw_string("FROZEN", 500, 60, 0x0000FF);
    }

    if (time != NULL) {
        char ts[9];
        ts[0] = '0' + time->hours / 10;
        ts[1] = '0' + time->hours % 10;
        ts[2] = ':';
        ts[3] = '0' + time->minutes / 10;
        ts[4] = '0' + time->minutes % 10;
        ts[5] = ':';
        ts[6] = '0' + time->seconds / 10;
        ts[7] = '0' + time->seconds % 10;
        ts[8] = '\0';

        font_draw_string(ts, 680, 15, 0xFFFFFF);
    }
}

void ui_render_level_complete(int suns_spent) {

    vg_draw_rectangle(220, 200, 360, 260, 0x111111);

    font_draw_string("LEVEL COMPLETE!", 310, 230, 0xFFFFFF);
    
    font_draw_string("SUNS SPENT:", 304, 280, 0xFFFFFF);
    font_draw_number(suns_spent, 448, 280, 0xFFFFFF);

    font_draw_string("PRESS ESC TO RETURN", 286, 340, 0xFFFFFF);
    if(current_level < 10){
        font_draw_string("PRESS ENTER FOR NEXT LEVEL", 256, 390, 0x00FF00);
    }
    else{
        font_draw_string("YOU COMPLETED THE GAME!! THX FOR PLAYING :)", 292, 420, 0x00FF00);
    }
}

void ui_render_game_over(int suns_spent) {
    vg_draw_rectangle(220, 200, 360, 260, 0x111111);

    font_draw_string("GAME OVER!", 340, 240, 0xFF0000); 
    
    font_draw_string("SUNS SPENT:", 304, 300, 0xFFFFFF);
    font_draw_number(suns_spent, 448, 300, 0xFFFFFF);

    font_draw_string("PRESS ESC TO RETURN", 286, 380, 0xFFFFFF);
}
