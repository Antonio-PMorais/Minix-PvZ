#ifndef __WAVE_MANAGER_H
#define __WAVE_MANAGER_H

#include <stdbool.h>

void wave_manager_init(int level_number);
void wave_manager_update();
bool wave_manager_is_complete();

#endif
