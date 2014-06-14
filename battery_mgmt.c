#include "battery_mgmt.h"
#include "temp.h"
#include "interrupt.h"

static bool_t battery_charging;

uint16_t get_battery_voltage(){
	uint16_t bat_volt;
	DI();
	select_adc_channel(BATTERY_VOL_MON);
	do_adc_conversion();
	bat_volt = load_adc_result();
	EI();
	return bat_volt;
}

bool_t is_battery_charging(){
	return battery_charging;
}

void battery_mgmt()
{
}

battery_voltage_t check_battery_voltage(void) {
	uint8_t loop0;
	battery_voltage_t return_val;
	uint16_t adc_int_val;

	bat_vol = 0;
	return_val = Low;
	adc_int_val = 0;

	select_adc_channel(BATTERY_VOL_MON);
	for (loop0=0; loop0<4; loop0++) {
		do_adc_conversion();
		adc_int_val = load_adc_result();
		bat_vol = bat_vol + adc_int_val;
	}
	bat_vol = bat_vol >> 2;
	bat_vol = bat_vol & 0x3FF;

	if (bat_vol <= BAT_LO_VOL) {
		return_val = Low;
	}
	else if (bat_vol >= BAT_HI_VOL) {
		return_val = High;
	}
	else {
		return_val = Mid;
	}

	return return_val;
}

battery_mgmt_init()
{
	LATC3 = 0; //o/p is one by default so that load is off
	pwm_init(BATT_CHARGING_PWM);
  	update_pwm_duty_cycle(BATT_CHARGING_PWM, 0);
  	//set_pwm_polarity(BATT_CHARGING_PWM, ACTIVE_LOW);
	enable_pwm(BATT_CHARGING_PWM);
	battery_charging = false;
}
