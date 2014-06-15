#ifndef __BATTERY_MGMT_H__
#define __BATTERY_MGMT_H__
#include "config.h"
#include "temp.h"
#include "common.h"


typedef enum {
  Low = 1,
  High = 2,
  Mid = 3
} battery_voltage_t;

typedef enum{
	FREE_CHARGING,
	CC,
	CV,
	TICKLE,
}battery_charging_state_t;

uint16_t get_battery_voltage();
bool_t is_battery_charging();
void battery_mgmt();
battery_mgmt_init();
#endif
