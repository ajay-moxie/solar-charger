#ifndef __BATTERY_PI_H__
#define __BATTERY_PI_H__
#include <htc.h>
#include <stdint.h>
#include "common.h"
#include "SYSTEM.h"
#include "intensity_switch.h"
#include "ADC.h"
#include "TIMER.h"
#include "PWM.h"
#include "Load_Switch.h"
#include "LED.h"
#include "pi.h"


uint16_t batt_charge;

state_t switch_val;
void charge_battery(void);
void set_battery_pi_state(state_t state);
void set_battery_error(bool_t error);
void set_battery_sticky_error(bool_t error);
void battery_pi_init();
sleep_t battery_power_state();
#endif
