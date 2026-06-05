#ifndef __UI_H
#define __UI_H

#include <stdint.h>
#include <stdbool.h>
#include "rtc.h"

void hud_init();

void ui_render_hud(int suns, int scr, int lvl, int selected_plant, bool is_frozen, bool is_shovel_mode, rtc_date *time);
void ui_render_level_complete(int suns_spent);
void ui_render_game_over(int suns_spent);

#endif
