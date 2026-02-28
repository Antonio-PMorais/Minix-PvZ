#include "rtc.h"
#include <minix/syslib.h>
#include <stdbool.h>

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

static int bdc_to_bin(uint8_t bcd) {
  uint8_t first_digit, second_digit;
  first_digit = (bcd & 0xF0)>>4;
  second_digit = (bcd & 0x0F);
  return first_digit * 10 + second_digit;
}

int rtc_read_date(rtc_date *date) {
  uint32_t value;

  // Wait for the UIP bit to be 0
  if (sys_outb(RTC_ADDR_REG, RTC_REG_A) != 0) {return 1;}
  if (sys_inb(RTC_DATA_REG, &value) != 0) {return 1;}

  while (value & RTC_UIP_MSK) {
    if (sys_outb(RTC_ADDR_REG, RTC_REG_A) != 0) {return 1;}
    if (sys_inb(RTC_DATA_REG, &value) != 0) {return 1;}
  }

  // Check for BCD format
  if (sys_outb(RTC_ADDR_REG, RTC_REG_B) != 0) {return 1;}
  if (sys_inb(RTC_DATA_REG, &value) != 0) {return 1;}
  bool is_bcd_format = !(value & RTC_DM_MSK);

  // Read the day
  if (sys_outb(RTC_ADDR_REG, RTC_REG_DAY) != 0) {return 1;}

  if (sys_inb(RTC_DATA_REG, &value) != 0) {return 1;}
  uint8_t day = (uint8_t) value;
  if (is_bcd_format) {day = bdc_to_bin(day);}
  date->day = day;

  // Read the month
  if (sys_outb(RTC_ADDR_REG, RTC_REG_MONTH) != 0) {return 1;}

  if (sys_inb(RTC_DATA_REG, &value) != 0) {return 1;}
  uint8_t month = (uint8_t) value;
  if (is_bcd_format) {month = bdc_to_bin(month);}
  date->month = month;

  // Read the year
  if (sys_outb(RTC_ADDR_REG, RTC_REG_YEAR) != 0) {return 1;}

  if (sys_inb(RTC_DATA_REG, &value) != 0) {return 1;}
  uint8_t year = (uint8_t) value;
  if (is_bcd_format) {year = bdc_to_bin(year);}
  date->year = year;

  return 0;
}
