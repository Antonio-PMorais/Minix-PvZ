#ifndef LEVELS_H
#define LEVELS_H

#include <stdint.h>

#define MAX_WAVES 10
#define MAX_ZOMBIES_PER_WAVE 20

typedef struct {
    uint8_t type;
    uint8_t lane;
} ZombieSpawnConfig;

typedef struct {
    int num_zombies;
    ZombieSpawnConfig spawns[MAX_ZOMBIES_PER_WAVE];
    int time_to_next_wave; 
} Wave;

typedef struct {
    int initial_delay; 
    int total_waves;
    Wave waves[MAX_WAVES];
} LevelConfig;

static const LevelConfig ALL_LEVELS[] = {
    
    // LEVEL 1
    {
        .initial_delay = 15, 
        .total_waves = 2,
        .waves = {
            { .num_zombies = 2, .spawns = {{1, 1}, {1, 2}}, .time_to_next_wave = 10 },
            
            { .num_zombies = 1, .spawns = {{1, 2}}, .time_to_next_wave = 3 }
        }
    }
    
    // Add additional levels here
};

#endif // LEVELS_H
