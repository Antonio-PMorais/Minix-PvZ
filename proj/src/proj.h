#ifndef _PROJ_H_
#define _PROJ_H_

#include <stdint.h>

#define VIDEO_MODE 0x115 
#define FPS 60

extern uint8_t timer_bit_no;
extern uint8_t kbd_bit_no;
extern uint8_t mouse_bit_no;
extern uint8_t rtc_bit_no;

int system_init();
int system_cleanup();

#endif
