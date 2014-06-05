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
#include "Charging.h"
#include "pi.h"

//Analog Channels
#define CHARGER_SENSE 10
#define OVERLOAD_SENSE 11
#define LOAD_VOLTAGE 6
#define TEMP_COMP 3

//Update all vairables for 2mV adc resolution

//PV constants
#define CHARGING_START_VOL 30 //PV is 150mV higher at RB4
#define CHARGER_DET 800 //PV is 4V higher at RB4
#define HYS_VOL 94 //460mV
#define BATT_CC_VOL 188 //940mV should be less than CHARGER_SETPOINT



typedef enum {
  LOAD_REG_50 = 8,
  LOAD_REG_100 = 9,
  OPEN_CKT_LOAD = 10,
  SHORT_CKT_LOAD = 11
} load_regulation_t;


uint16_t charger_vol;
uint16_t load_vol;
uint16_t batt_charge;
uint8_t hysterisis_flag;
uint8_t count;

state_t switch_val;
uint8_t first_run;
uint16_t pv_det_count;
uint16_t stop_charging_count;

//ADC functions
//ovp_mon_t monitor_overload_voltage(void);
void init_adc_var(void);
void configure_adc(void);
void init_vars(void);
void enable_tmr2_int(void);
void load_connect(void);
void batt_charger_fun(void);
void set_load_state(state_t state);
void set_load_error(bool_t error);
void set_load_sticky_error(bool_t error);
void led_load_pi_init();
sleep_t load_power_state();
#endif
