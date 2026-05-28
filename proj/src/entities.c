#include "entities.h"
#include "v_card.h"

// colors 
#define COL_PEA     0x90EE90
#define COL_ZOMBIE  0x444444
#define COL_ZHEAD   0x90EE90
#define COL_ZEYE    0xFF0000
#define COL_FROZEN  0x0000FF
#define COL_SUN     0xFFFF00
#define COL_SUNCORE 0xFFA500

// entity arrays
zombie_t zombies[MAX_ZOMBIES];
projectile_t projectiles[MAX_PROJECTILES];
sun_t suns_array[MAX_SUNS];


