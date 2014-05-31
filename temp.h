#ifndef __temp_h__
#define __temp_h__
#include <htc.h>
#include <stdint.h>

#include "SYSTEM.h"
#include "Intensity_Switch.h"
#include "ADC.h"
#include "TIMER.h"
#include "PWM.h"
#include "Load_Switch.h"
#include "LED.h"
#include "Charging.h"
#include "battery_mgmt.h"
#include "common.h"

#define SW_OFF_PV_N ((switch_val == OFF) && (charger_check == No))
#define SW_OFF_PV_Y ((switch_val == OFF) && (charger_check == Yes))
#define SW_ON_PV_N ((switch_val == ON) && (charger_check == No))
#define SW_ON_PV_Y ((switch_val == ON) && (charger_check == Yes))

//Analog Channels
#define CHARGER_SENSE 10
#define OVERLOAD_SENSE 11
#define LOAD_VOLTAGE 6
#define BATTERY_VOL_MON 9
#define BATTERY_CHARGE_VOL 8
#define TEMP_COMP 3
#define MOBILE_CHARGE_SENSE 0
#define MOBILE_BATT_VOL_MON 4

//Update all vairables for 2mV adc resolution

//PV constants
#define CHARGING_START_VOL 30 //PV is 150mV higher at RB4
#define CHARGER_DET 800 //PV is 4V higher at RB4
#define HYS_VOL 94 //460mV
#define BATT_CC_VOL 188 //940mV should be less than CHARGER_SETPOINT

//LED constants
#define OVP_VOL 177 //59V
#define LOAD_OPEN_CKT_VOL 1
#define LOAD_SHORT_CKT_VOL 1000


typedef enum {
  Yes = 4,
  No = 5
} charger_present_t;


typedef enum {
  CHARGER_PWM_CTL_REQ = 12,
  CHARGER_PWM_CTL_NOT_REQ = 13
} charging_stage_t;

typedef enum {
  THERMISTOR_VOL = 14
} thermistor_vol_t;

uint16_t bat_vol;
uint16_t ovp_vol;
uint16_t charger_vol;
uint16_t load_vol;
uint16_t batt_charge;
uint16_t thermistor_voltage;
uint8_t hysterisis_flag;
uint8_t count;

state_t switch_val;
//battery_voltage_t battery_check;
charger_present_t charger_check;
uint8_t first_run;
uint16_t pv_det_count;
uint16_t stop_charging_count;

//ADC functions
void config_analog_pins(void);
charger_present_t check_charger_present(void);
charging_stage_t battery_charge_monitor(void);
void init_adc_var(void);
void configure_adc(void);
void init_vars(void);
void enable_tmr2_int(void);
void batt_charger_fun(void);
void disp_low_batt_n_enter_sleep(void);
#endif
