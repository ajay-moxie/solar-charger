#include "battery_mgmt.h"
#include "temp.h"
#include "interrupt.h"
#include "battery_pi.h"

static state_t battery_charging;
static uint16_t battery_voltage;
static battery_charging_stage_t charging_stage;

void set_charging_stage(battery_charging_stage_t stage)
{
	charging_stage = stage;
}

battery_charging_stage_t get_charging_stage()
{
	return charging_stage;
}
void measure_battery_voltage(){
	uint16_t bat_volt;
	DI();
	select_adc_channel(BATTERY_VOL_MON);
	do_adc_conversion();
	bat_volt = load_adc_result();
	EI();
	battery_voltage = bat_volt;
}

uint16_t get_battery_voltage(){
	return battery_voltage;
}

state_t battery_charging_state(){
	return battery_charging;
}

void set_battery_charging_state(state_t state){
	battery_charging = state;
}

bool_t battery_charging_needed(){
	if(battery_voltage < BAT_HI_VOL)
		return true;
	else 
		return false;
}
void battery_mgmt()
{
	static uint16_t count = 0;
	uint16_t current;
	set_battery_pi_state(ON);	
	if((battery_voltage >= BATT_CV_VOLT) && (charging_stage == CC)){
		count++;
		if(count == 1000){
			DI();
			battery_pi_init();
			charging_stage = CV;
			set_battery_pi_setpoint(BATT_CV_VOLT);
			count = 0;
			set_battery_pi_state(ON);
			EI();
		}
	}
	else if(charging_stage == CV){
		select_adc_channel(BATT_CHARGING_ADC);
		do_adc_conversion();
		current = load_adc_result();
		if(current < BATT_CV_CURRENT_LIMIT){
			set_battery_pi_state(OFF);	
			set_battery_charging_state(OFF);
			charging_stage = CC;
		}
	}
}

/*static battery_voltage_t check_battery_voltage(void) {
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
}*/

battery_mgmt_init()
{
	LATC3 = BATT_CHARGING_INIT_VALUE; //o/p is one by default so that load is off
	pwm_init(BATT_CHARGING_PWM);
  	update_pwm_duty_cycle(BATT_CHARGING_PWM, 0x0);
  	set_pwm_polarity(BATT_CHARGING_PWM, BATT_CHARING_POLARTIY);
	enable_pwm(BATT_CHARGING_PWM);
	battery_charging = OFF;
	set_charging_stage(CC);
}
