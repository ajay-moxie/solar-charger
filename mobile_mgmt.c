#include "common.h"
#include "load_mgmt.h"
#include "battery_mgmt.h"
#include "led_load.h"
#include "interrupt.h"
#include "temp.h"
#include "PWM.h"

static uint16_t load_volt;
static ovp_mon_t ovp_cond;
static state_t mobile_charging;
static monitor_mobile_voltage(void) {
	uint8_t i;
	
	DI();
	select_adc_channel(LED_LOAD_OVERLOAD_SENSE);
	do_adc_conversion();
	load_volt = load_adc_result();
	EI();

}

state_t mobile_charging_state(){
	return mobile_charging;
}

void set_mobile_charging_state(state_t state){
	mobile_charging = state;
}

void mobile_mgmt()
{
	static bool_t error = false;
	bool_t sticky_error = false;
	uint16_t batt_volt;
	monitor_mobile_voltage();
	if (load_volt >= OVP_VOL) {
		set_load_sticky_error(true);
		display_ovp_fault();
		sticky_error = true;
	}

	batt_volt = get_battery_voltage();

	if(batt_volt < BAT_LO_VOL) {
		set_load_error(true);
		display_ovp_fault();
		error = true;
	}
	else if(batt_volt >= BAT_RECONNECT_VOL){
		error = false;
	}

	if(error == false){
		set_load_error(false);
	}
}

void mobile_mgmt_init()
{
	LATC5 = MOBILE_CHARGING_SWITCH_INIT_VALUE; //o/p is one by default so that load is off
	pwm_init(MOBILE_CHARGING_PWM);
  	update_pwm_duty_cycle(MOBILE_CHARGING_PWM, 0);
  	set_pwm_polarity(MOBILE_CHARGING_PWM, MOBILE_CHARGING_POLARTIY);
	enable_pwm(MOBILE_CHARGING_PWM);
	mobile_charging = OFF;
}
