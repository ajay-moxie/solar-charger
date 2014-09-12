#ifndef __MOBILE_PI_H__
#define __MOBILE_PI_H__
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
void charge_mobile(void);
void set_mobile_pi_state(state_t state);
void set_mobile_error(bool_t error);
void set_mobile_sticky_error(bool_t error);
void mobile_pi_init();
sleep_t mobile_power_state();
void set_mobile_pi_setpoint(uint16_t setpoint);
#endif
