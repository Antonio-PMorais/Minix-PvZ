#include "v_card.h"

static void *video_mem;       // Process (virtual) address to which VRAM is mapped
static vbe_mode_info_t vmi_p; // VBE mode info

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

void *(vg_init)(uint16_t mode) {
    //get vbe mode information
    if (vbe_get_mode_info(mode, &vmi_p) != 0) {
        printf("vbe_get_mode_info failed\n");
        return NULL;
    }

    //map physical memory to virtual memory
    int r;
    struct minix_mem_range mr;
    unsigned int vram_base = vmi_p.PhysBasePtr;
    unsigned int vram_size = vmi_p.XResolution * vmi_p.YResolution * ((vmi_p.BitsPerPixel + 7) / 8);

    //allow memory mapping
    mr.mr_base = (phys_bytes) vram_base;
    mr.mr_limit = mr.mr_base + vram_size;

    if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) {
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    }

    //map memory
    video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
    if (video_mem == MAP_FAILED) {
        panic("couldn't map video memory");
    }

    //change vbe mode
    if (change_mode(mode) != 0) {
        return NULL;
    }

    return video_mem;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    //check out of bounds
    if (x >= vmi_p.XResolution || y >= vmi_p.YResolution) {
        return 0; 
    }

    unsigned int bytes_per_pixel = (vmi_p.BitsPerPixel + 7) / 8;
    unsigned int index = (vmi_p.XResolution * y + x) * bytes_per_pixel;

    //moving the exact number of bytes needed
    memcpy((uint8_t*)video_mem + index, &color, bytes_per_pixel);

    return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    for (unsigned i = 0; i < len; i++) {
        vg_draw_pixel(x + i, y, color);
    }
    return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    for (unsigned i = 0; i < height; i++) {
        vg_draw_hline(x, y + i, width, color);
    }
    return 0;
}
