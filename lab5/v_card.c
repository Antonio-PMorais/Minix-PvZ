#include "v_card.h"

int(change_mode)(uint16_t mode) {
    reg86_t reg86;

    memset(&reg86, 0, sizeof(reg86)); //clean struct values

    reg86.intno = 0x10;          //video interrupt
    reg86.ax = 0x4F02;           //set VBE mode
    
    reg86.bx = (mode | BIT(14)) & ~BIT(15); //ensure linear frame buffer && avoid cleaning screen between mode changes

    if (sys_int86(&reg86) != OK) {   //send instruction
        printf("\tvg_init(): sys_int86() failed \n");
        return 1;
    }

    return 0;
}
