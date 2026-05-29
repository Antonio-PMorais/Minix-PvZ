#include "entities.h"

#include "v_card.h"


// colors (24-bit, same format as game.c uses)

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


void entities_init() {

    for (int i = 0; i < MAX_ZOMBIES; i++) zombies[i].active = false;

    for (int i = 0; i < MAX_PROJECTILES; i++) projectiles[i].active = false;

    for (int i = 0; i < MAX_SUNS; i++) suns_array[i].active = false;

}


void spawn_zombie(uint8_t lane, int level) {

    for (int i = 0; i < MAX_ZOMBIES; i++) {

        if (!zombies[i].active) {

            zombies[i].active = true;

            zombies[i].x = 780;

            zombies[i].lane = lane;

            zombies[i].hp = 250 + level * 20;

            zombies[i].speed = 2;

            zombies[i].eating = false;

            zombies[i].eat_timer = 0;

            return;

        }

    }

}


void spawn_projectile(uint8_t lane, int16_t x, int16_t y) {

    for (int i = 0; i < MAX_PROJECTILES; i++) {

        if (!projectiles[i].active) {

            projectiles[i].active = true;

            projectiles[i].x = x;

            projectiles[i].y = y;

            projectiles[i].lane = lane;

            projectiles[i].damage = 20;

            return;

        }

    }

}


void spawn_sun(int16_t x, int16_t start_y, int16_t target_y) {

    for (int i = 0; i < MAX_SUNS; i++) {

        if (!suns_array[i].active) {

            suns_array[i].active = true;

            suns_array[i].x = x;

            suns_array[i].y = start_y;

            suns_array[i].target_y = target_y;

            suns_array[i].lifetime = 600;

            return;

        }

    }

}


int entities_zombies_alive() {

    int count = 0;

    for (int i = 0; i < MAX_ZOMBIES; i++)

        if (zombies[i].active) count++;

    return count;

}


bool entities_collect_sun(int16_t mx, int16_t my, int *suns_count) {

    for (int i = 0; i < MAX_SUNS; i++) {

        if (!suns_array[i].active) continue;

        if (mx >= suns_array[i].x - 15 && mx <= suns_array[i].x + 15 &&

            my >= suns_array[i].y - 15 && my <= suns_array[i].y + 15) {

            *suns_count += 25;

            suns_array[i].active = false;

            return true;

        }

    }

    return false;

}


// grid constants must match game.c

#define GRID_START_X 40

#define GRID_COLS    9

#define CELL_SIZE    80


bool entities_update(plant_cell_t grid[5][9], int *suns_count, int *score,

                     int level, bool frozen, uint32_t tc) {


    // update plants — shooting and sun generation

    for (int r = 0; r < 5; r++) {

        for (int c = 0; c < 9; c++) {

            if (grid[r][c].type == 2) { // peashooter

                grid[r][c].shoot_timer++;

                if (grid[r][c].shoot_timer >= 84) {

                    grid[r][c].shoot_timer = 0;

                    // only shoot if zombie in lane

                    bool has_zombie = false;
                    int plant_x = GRID_START_X + c * CELL_SIZE;

                    for (int z = 0; z < MAX_ZOMBIES; z++){

                        if (zombies[z].active && zombies[z].lane == r) {
                            if (zombies[z].x > plant_x) {
                                has_zombie = true; 
                                break;
                            }
                        }
                    }
                    if (has_zombie) {

                        grid[r][c].shoot_timer = 0;
                        int px = plant_x + CELL_SIZE;
                        int py = 150 + r * CELL_SIZE + CELL_SIZE / 2;
                        spawn_projectile(r, px, py);

                    }

                }

            }

            else if (grid[r][c].type == 1) { // sunflower

                grid[r][c].sun_timer++;

                if (grid[r][c].sun_timer >= 1440) {

                    grid[r][c].sun_timer = 0;

                    int sx = GRID_START_X + c * CELL_SIZE + 20 + (rand() % 40);

                    int sy = 150 + r * CELL_SIZE + 20 + (rand() % 40);

                    spawn_sun(sx, sy, sy);

                }

            }

        }

    }


    // update projectiles

    for (int i = 0; i < MAX_PROJECTILES; i++) {

        if (!projectiles[i].active) continue;

        projectiles[i].x += 4;

        if (projectiles[i].x > 800) { projectiles[i].active = false; continue; }


        // check hit zombie

        for (int z = 0; z < MAX_ZOMBIES; z++) {

            if (!zombies[z].active || zombies[z].lane != projectiles[i].lane) continue;

            if (projectiles[i].x >= zombies[z].x - 5 && projectiles[i].x <= zombies[z].x + 30) {

                zombies[z].hp -= projectiles[i].damage;

                projectiles[i].active = false;

                if (zombies[z].hp <= 0) {

                    zombies[z].active = false;

                    *score += 10;

                }

                break;

            }

        }

    }


    // update suns

    for (int i = 0; i < MAX_SUNS; i++) {

        if (!suns_array[i].active) continue;

        if (suns_array[i].y < suns_array[i].target_y) suns_array[i].y += 1;

        suns_array[i].lifetime--;

        if (suns_array[i].lifetime == 0) suns_array[i].active = false;

    }


    // update zombies

    for (int z = 0; z < MAX_ZOMBIES; z++) {

        if (!zombies[z].active) continue;

        if (frozen) continue;


        int col = (zombies[z].x - GRID_START_X) / CELL_SIZE;

        int row = zombies[z].lane;


        if (col >= 0 && col < GRID_COLS && grid[row][col].type != 0 &&

            zombies[z].x <= GRID_START_X + (col + 1) * CELL_SIZE) {

            // eating plant

            zombies[z].eating = true;

            zombies[z].eat_timer++;

            if (zombies[z].eat_timer >= 60) {

                zombies[z].eat_timer = 0;

                grid[row][col].hp -= 100;

                if (grid[row][col].hp <= 0) {

                    grid[row][col].type = 0;

                    zombies[z].eating = false;

                }

            }

        } else {

            zombies[z].eating = false;

            zombies[z].eat_timer = 0;

            if (tc % 7 == 0) {
                zombies[z].x -= zombies[z].speed;
            }

        }


        // game over check

        if (zombies[z].x <= GRID_START_X - 30) {

            return true; // game over

        }

    }


    // drop suns from sky (using timer_counter)

    if (tc % 300 == 0) {

        int16_t sx = GRID_START_X + (rand() % (GRID_COLS * CELL_SIZE));
        int16_t sy = 150 + (rand() % (5 * CELL_SIZE));
        spawn_sun(sx, 0, sy);

    }


    return false; // not game over

}


void entities_render(int grid_x, int grid_y, int cell_h, bool frozen) {

    // projectiles

    for (int i = 0; i < MAX_PROJECTILES; i++) {

        if (!projectiles[i].active) continue;

        vg_draw_rectangle(projectiles[i].x, projectiles[i].y - 4, 8, 8, COL_PEA);

    }


    // zombies

    for (int z = 0; z < MAX_ZOMBIES; z++) {

        if (!zombies[z].active) continue;

        int zy = grid_y + zombies[z].lane * cell_h + 10;

        uint32_t col = frozen ? COL_FROZEN : COL_ZOMBIE;

        vg_draw_rectangle(zombies[z].x, zy, 25, 55, col);

        vg_draw_rectangle(zombies[z].x + 3, zy - 15, 20, 18, COL_ZHEAD);

        vg_draw_rectangle(zombies[z].x + 7, zy - 10, 4, 4, COL_ZEYE);

        vg_draw_rectangle(zombies[z].x + 15, zy - 10, 4, 4, COL_ZEYE);

    }


    // suns

    for (int i = 0; i < MAX_SUNS; i++) {

        if (!suns_array[i].active) continue;

        vg_draw_rectangle(suns_array[i].x - 12, suns_array[i].y - 12, 24, 24, COL_SUN);

        vg_draw_rectangle(suns_array[i].x - 8, suns_array[i].y - 8, 16, 16, COL_SUNCORE);

    }

}
