#include "bitwise.h"

#define TODO return 255

uint8_t clear(uint8_t msk, int pos) {
  return msk & ~(1 << pos);
}

uint8_t set(uint8_t msk, int pos) {
  return msk | (1 << pos);
}

bool is_set(uint8_t msk, int pos) {
  return msk & (1 << pos);
}

uint8_t lsb(uint16_t wide_msk) {
  return wide_msk & 0xFF;
}

uint8_t msb(uint16_t wide_msk) {
  return wide_msk >> 8;
}

uint8_t mask(int pos, ...) {
  uint8_t res = 0x00;
  int *p = &pos;
  int cur_pos;

  while(*p != MSK_END) {
    cur_pos = *p;

    if(cur_pos >= 0 && cur_pos <= 7){
      res |= (1 << cur_pos);
    }

    p++;
  }

  return res;
}
