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
            { .num_zombies = 2, .spawns = {{1, 1}, {1, 2}}, .time_to_next_wave = 5 },
            
            { .num_zombies = 1, .spawns = {{1, 2}}, .time_to_next_wave = 3 }
        }
    },
    
 // LEVEL 2 - 3 waves
    {
        .initial_delay = 12,
        .total_waves = 3,
        .waves = {
            { .num_zombies = 2, .spawns = {{1, 0}, {1, 4}}, .time_to_next_wave = 6 },
            { .num_zombies = 3, .spawns = {{1, 1}, {1, 2}, {1, 3}}, .time_to_next_wave = 5 },
            { .num_zombies = 2, .spawns = {{1, 0}, {1, 4}}, .time_to_next_wave = 0 }
        }
    },
 
    // LEVEL 3 - more zombies per wave
    {
        .initial_delay = 12,
        .total_waves = 3,
        .waves = {
            { .num_zombies = 3, .spawns = {{1, 0}, {1, 2}, {1, 4}}, .time_to_next_wave = 5 },
            { .num_zombies = 4, .spawns = {{1, 0}, {1, 1}, {1, 3}, {1, 4}}, .time_to_next_wave = 4 },
            { .num_zombies = 3, .spawns = {{1, 1}, {1, 2}, {1, 3}}, .time_to_next_wave = 0 }
        }
    },
 
    // LEVEL 4 - faster waves
    {
        .initial_delay = 10,
        .total_waves = 4,
        .waves = {
            { .num_zombies = 3, .spawns = {{1, 0}, {1, 2}, {1, 4}}, .time_to_next_wave = 4 },
            { .num_zombies = 3, .spawns = {{1, 1}, {1, 2}, {1, 3}}, .time_to_next_wave = 4 },
            { .num_zombies = 4, .spawns = {{1, 0}, {1, 1}, {1, 3}, {1, 4}}, .time_to_next_wave = 3 },
            { .num_zombies = 2, .spawns = {{1, 0}, {1, 4}}, .time_to_next_wave = 0 }
        }
    },
 
    // LEVEL 5 - all lanes at once
    {
        .initial_delay = 10,
        .total_waves = 4,
        .waves = {
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 5 },
            { .num_zombies = 3, .spawns = {{1,0},{1,2},{1,4}}, .time_to_next_wave = 4 },
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 4 },
            { .num_zombies = 3, .spawns = {{1,1},{1,2},{1,3}}, .time_to_next_wave = 0 }
        }
    },
 
    // LEVEL 6 - bigger waves, shorter breaks
    {
        .initial_delay = 8,
        .total_waves = 5,
        .waves = {
            { .num_zombies = 4, .spawns = {{1,0},{1,1},{1,3},{1,4}}, .time_to_next_wave = 4 },
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 3 },
            { .num_zombies = 3, .spawns = {{1,0},{1,2},{1,4}}, .time_to_next_wave = 4 },
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 3 },
            { .num_zombies = 4, .spawns = {{1,0},{1,1},{1,3},{1,4}}, .time_to_next_wave = 0 }
        }
    },
 
    // LEVEL 7 - double zombies in lanes
    {
        .initial_delay = 8,
        .total_waves = 5,
        .waves = {
            { .num_zombies = 4, .spawns = {{1,0},{1,0},{1,2},{1,4}}, .time_to_next_wave = 4 },
            { .num_zombies = 6, .spawns = {{1,0},{1,1},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 3 },
            { .num_zombies = 4, .spawns = {{1,1},{1,2},{1,3},{1,3}}, .time_to_next_wave = 4 },
            { .num_zombies = 6, .spawns = {{1,0},{1,0},{1,2},{1,2},{1,4},{1,4}}, .time_to_next_wave = 3 },
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 0 }
        }
    },
 
    // LEVEL 8 - heavy assault
    {
        .initial_delay = 7,
        .total_waves = 6,
        .waves = {
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 3 },
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 3 },
            { .num_zombies = 4, .spawns = {{1,0},{1,0},{1,4},{1,4}}, .time_to_next_wave = 3 },
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 3 },
            { .num_zombies = 6, .spawns = {{1,0},{1,1},{1,1},{1,3},{1,3},{1,4}}, .time_to_next_wave = 2 },
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 0 }
        }
    },
 
    // LEVEL 9 - fast and relentless
    {
        .initial_delay = 6,
        .total_waves = 7,
        .waves = {
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 3 },
            { .num_zombies = 6, .spawns = {{1,0},{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 2 },
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 3 },
            { .num_zombies = 6, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4},{1,4}}, .time_to_next_wave = 2 },
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 3 },
            { .num_zombies = 7, .spawns = {{1,0},{1,0},{1,1},{1,2},{1,3},{1,4},{1,4}}, .time_to_next_wave = 2 },
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 0 }
        }
    },
 
    // LEVEL 10 - final level, maximum difficulty
    {
        .initial_delay = 5,
        .total_waves = 8,
        .waves = {
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 3 },
            { .num_zombies = 6, .spawns = {{1,0},{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 2 },
            { .num_zombies = 7, .spawns = {{1,0},{1,0},{1,1},{1,2},{1,3},{1,4},{1,4}}, .time_to_next_wave = 2 },
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 3 },
            { .num_zombies = 8, .spawns = {{1,0},{1,0},{1,1},{1,1},{1,2},{1,3},{1,4},{1,4}}, .time_to_next_wave = 2 },
            { .num_zombies = 5, .spawns = {{1,0},{1,1},{1,2},{1,3},{1,4}}, .time_to_next_wave = 2 },
            { .num_zombies = 8, .spawns = {{1,0},{1,0},{1,1},{1,2},{1,2},{1,3},{1,4},{1,4}}, .time_to_next_wave = 2 },
            { .num_zombies = 10, .spawns = {{1,0},{1,0},{1,1},{1,1},{1,2},{1,2},{1,3},{1,3},{1,4},{1,4}}, .time_to_next_wave = 0 }
        }
    }


};

#endif // LEVELS_H
