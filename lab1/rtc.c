#include <minix/syslib.h>
#include <lcom/lcf.h>
#include "rtc.h"

#define TODO return -1

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_REG_A 0x0A
#define RTC_REG_B 0x0B
#define RTC_REG_DAY 0x07
#define RTC_REG_MONTH 0x08
#define RTC_REG_YEAR 0x09
#define RTC_UIP_MSK (1 << 7)
#define RTC_DM_MSK (1 << 2)

static int bcd_to_bin(uint8_t bcd) {
  return (bcd & 0x0F) + ((bcd >> 4) * 10);
}

int rtc_read_date(rtc_date *date) {
  uint32_t uid, dm, sec, min, hour, day, month, year;
  
  do{
    sys_outb(0x70, 0x0A);
    sys_inb(0x71, &uid);
  } while (uid & 0x80);

  sys_outb(0x70, 0x0B);
  sys_inb(0x71, &dm);

  sys_outb(0x70, 0x00);
  sys_inb(0x71, &sec);

  sys_outb(0x70, 0x02);
  sys_inb(0x71, &min);

  sys_outb(0x70, 0x04);
  sys_inb(0x71, &hour);

  sys_outb(0x70, 0x07);
  sys_inb(0x71, &day);

  sys_outb(0x70, 0x08);
  sys_inb(0x71, &month);

  sys_outb(0x70, 0x09);
  sys_inb(0x71, &year);

  if (!(dm & 0x04)) {
    day   = bcd_to_bin(day);
    month = bcd_to_bin(month);
    year  = bcd_to_bin(year);
  }

  date->day = day;
  date->month = month;
  date->year = year;

  return 0;
}
