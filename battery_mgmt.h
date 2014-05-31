#ifndef __BATTERY_MGMT_H__
#define __BATTERY_MGMT_H__
#include "config.h"
#include "temp.h"


typedef enum {
  Low = 1,
  High = 2,
  Mid = 3
} battery_voltage_t;

battery_voltage_t check_battery_voltage(void);
uint16_t get_battery_voltage();
#endif
