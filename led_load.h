#ifndef __LED_LOAD_H__
#define __LED_LOAD_H__
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

//Update all vairables for 2mV adc resolution

typedef enum {
  LOAD_REG_50 = 8,
  LOAD_REG_100 = 9,
  OPEN_CKT_LOAD = 10,
  SHORT_CKT_LOAD = 11
} load_regulation_t;


uint16_t load_vol;
uint16_t batt_charge;

state_t switch_val;
void load_connect(void);
void set_load_state(state_t state);
void set_load_error(bool_t error);
void set_load_sticky_error(bool_t error);
void led_load_pi_init();
sleep_t load_power_state();
#endif
