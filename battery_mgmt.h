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
	CC,
	CV,
	TICKLE,
}battery_charging_stage_t;

void measure_battery_voltage();
uint16_t get_battery_voltage();
state_t battery_charging_state();
void battery_mgmt();
battery_mgmt_init();
void set_battery_charging_state(state_t state);
battery_charging_stage_t get_charging_stage();
bool_t battery_charging_needed();
#endif
