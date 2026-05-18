#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "proj.h"

#include <lcom/timer.h>
#include "keyboard.h"
#include "mouse.h"
#include "rtc.h"
#include "v_card.h"

uint8_t timer_bit_no;
uint8_t kbd_bit_no;
uint8_t mouse_bit_no;
uint8_t rtc_bit_no;

int system_init() {
    if (timer_set_frequency(0, FPS) != 0) {
        printf("Error: Failed to set Timer frequency.\n");
        return 1;
    }
    if (timer_subscribe_int(&timer_bit_no) != 0) {
        printf("Error: Failed to subscribe Timer interrupts.\n");
        return 1;
    }

    if (kbd_subscribe_int(&kbd_bit_no) != 0) {
        printf("Error: Failed to subscribe Keyboard interrupts.\n");
        return 1;
    }

    if (mouse_subscribe_int(&mouse_bit_no) != 0) {
        printf("Error: Failed to subscribe Mouse interrupts.\n");
        return 1;
    }
    if (mouse_enable_data_report() != 0) {
        printf("Error: Failed to enable Mouse data reporting.\n");
        return 1;
    }

    if (rtc_subscribe_int(&rtc_bit_no) != 0) {
        printf("Error: Failed to subscribe RTC interrupts.\n");
        return 1;
    }

    if (vg_init(VIDEO_MODE) == NULL) {
        printf("Error: Failed to initialize video mode.\n");
        return 1;
    }

    return 0;
}

int system_cleanup() {
    int errors = 0;

    if (vg_exit() != 0) {
        printf("Error: Failed to exit video mode.\n");
        errors = 1;
    }

    if (mouse_disable_data_report() != 0) {
        printf("Error: Failed to disable Mouse data reporting.\n");
        errors = 1;
    }
    if (mouse_unsubscribe_int() != 0) {
        printf("Error: Failed to unsubscribe Mouse.\n");
        errors = 1;
    }

    if (kbd_unsubscribe_int() != 0) {
        printf("Error: Failed to unsubscribe Keyboard.\n");
        errors = 1;
    }

    if (timer_unsubscribe_int() != 0) {
        printf("Error: Failed to unsubscribe Timer.\n");
        errors = 1;
    }

    if (rtc_unsubscribe_int() != 0) {
        printf("Error: Failed to unsubscribe RTC.\n");
        errors = 1;
    }

    return errors;
}

int main(int argc, char *argv[]) {
    lcf_set_language("EN-US");
    
    if (lcf_start(argc, argv)) return 1;
    
    lcf_cleanup();
    
    return 0;
}

int(proj_main_loop)(int argc, char *argv[]) {
    printf("Initializing system\n");

    if (system_init() != 0) {
        printf("System initialization failed. \n");
        system_cleanup();
        return 1;
    }

    sleep(3);

    if (system_cleanup() != 0) {
        printf("Failed to reset Minix state.\n");
        return 1;
    }

    printf("System shut down successfully.\n");
    return 0;
}
