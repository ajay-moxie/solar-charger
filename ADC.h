
#include <htc.h>
#include <stdint.h>

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

//Battery constants
#define BAT_HI_VOL 164 //for 13V
#define BAT_MID_VOL 140 //for 11V  
#define BAT_LO_VOL 129 //for 10.2V

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
  Low = 1,
  High = 2,
  Mid = 3
} battery_voltage_t;

typedef enum {
  Yes = 4,
  No = 5
} charger_present_t;

typedef enum {
  OVP_REACHED = 6,
  OVP_NOT_REACHED = 7
} ovp_mon_t;

typedef enum {
  LOAD_REG_50 = 8,
  LOAD_REG_100 = 9,
  OPEN_CKT_LOAD = 10,
  SHORT_CKT_LOAD = 11
} load_regulation_t;

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
