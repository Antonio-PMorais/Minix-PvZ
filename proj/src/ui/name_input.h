#ifndef __NAME_INPUT_H
#define __NAME_INPUT_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME_LEN 12

//initialize name input state 
void name_input_init();

// handle keyboard input, returns true when Enter is pressed 
bool name_input_on_key(uint8_t scancode);

// draw the name input screen
void name_input_render();

// get the current player name 
const char* name_input_get_name();

// get player name length
int name_input_get_length();

#endif
