
#include <htc.h>
#include <stdint.h>


//charger PWM period
#define CHARGER_PWM_PERIOD 250

//10% Duty cycle
#define CHARGER_DUTY_CYC_10 40
#define CHARGER_DUTY_CYC_10_U ((CHARGER_DUTY_CYC_10 & 0xFC) >> 2)
#define CHARGER_DUTY_CYC_10_L ((CHARGER_DUTY_CYC_10 & 0x03) << 6)
//6% Duty cycle
#define CHARGER_DUTY_CYC_05 20
#define CHARGER_DUTY_CYC_05_U ((CHARGER_DUTY_CYC_05 & 0xFC) >> 2)
#define CHARGER_DUTY_CYC_05_L ((CHARGER_DUTY_CYC_05 & 0x03) << 6)

//PI defines PV
#define CHARGER_KP 16
#define CHARGER_KI 2
#define CHARGER_DUTY_MAX 100 //90%
#define CHARGER_SETPOINT 194 //970 mV results in 2A current // adjust it for 2mV adc resolution
#define CHARGER_INTEGRAL_MIN -32000
#define CHARGER_INTEGRAL_MAX 32000
#define CHARGER_CONST_K 64

//Battery constants
#define BATT_CV_SWITCH_VOL 190 //14.9V     to be updated for 2mv resolution
//#define BATT_CV_VOL (BATT_CV_SWITCH_VOL * 0.9)
//#define CHARGER_CV_SETPOINT (BATT_CV_SWITCH_VOL * 0.9)
#define BATT_CV_VOL 184 //14.5V
#define CHARGER_CV_SETPOINT 184 //14.5V
#define STOP_CHARGING_VOL 30 //14.4V with 500mA current

uint8_t charger_Kp;
uint8_t charger_Ki;
uint16_t charger_duty_max;
uint16_t charger_setpoint;
uint16_t charger_feedback;
int16_t charger_error;
int16_t charger_integral;
uint16_t charger_duty_cycle;
uint8_t charger_saturated;
uint8_t start_CV_stage;
uint8_t start_charging;
