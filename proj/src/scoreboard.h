#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H

#include <stdint.h>
#include <stdbool.h>
#include "rtc.h"

#define MAX_SCORES 10

// single scoreboard entry 
typedef struct {
    char name[13];
    int score;
    int suns_spent;
    int level;
    rtc_date date;
    bool valid;
} score_entry_t;

// initialize scoreboard 
void scoreboard_init();

// add score after completing a level 
void scoreboard_add(const char *name, int level, int score, int suns_spent,
                    rtc_date *date);

// draw scoreboard screen 
void scoreboard_render();

// get best score for a level 
score_entry_t* scoreboard_get(int level);


#endif
