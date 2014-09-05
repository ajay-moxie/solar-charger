#include "common.h"
#include "config.h"
#include "pi.h"
#include "interrupt.h"
#include "pv_mgmt.h"
#include "PWM.h"
#include "battery_mgmt.h"

struct pi battery_pi;

static void stop_battery_charging(sleep_t sleep);

sleep_t battery_pi_power_state()
{
	return battery_pi.sleep_ready;
}
void set_battery_pi_state(state_t state)
{
	DI();
	battery_pi.state = state;
	EI();
}

void set_battery_pi_error(bool_t error)
{
	DI();
	battery_pi.error = error;
	EI();
}

void set_battery_pi_sticky_error(bool_t error)
{
	DI();
	battery_pi.sticky_error = error;
	EI();
}

static battery_pi_vars_init()
{
	battery_pi.setpoint = LED_LOAD_SETPOINT;
	battery_pi.pi_error = 0;
	battery_pi.integral = 0;
	battery_pi.duty_cycle = 0;
	battery_pi.saturated = 0;
	battery_pi.feedback = 0;
	battery_pi.duty_max = LED_LOAD_DUTY_MAX;
	battery_pi.Kp = LED_LOAD_KP;
	battery_pi.Ki = LED_LOAD_KI;

}
void battery_pi_init()
{
	battery_pi_vars_init();
	battery_pi.error = false;
	battery_pi.sticky_error = false;
	battery_pi.sleep_ready = false;
}

/*static load_regulation_t monitor_load_regulation(void) {
	uint8_t loop3;
	load_regulation_t return_val;

	load_vol = 0;
	return_val = OPEN_CKT_LOAD;

	select_adc_channel(LOAD_VOLTAGE);
	do_adc_conversion();
	load_vol = load_adc_result();
	

	if (load_vol <= LOAD_OPEN_CKT_VOL) {
		return_val = OPEN_CKT_LOAD;
	}
	else if (load_vol >= LOAD_SHORT_CKT_VOL) {
		return_val = SHORT_CKT_LOAD;
	}
	else {
		return_val = LOAD_REG_100;
	}

	return return_val;
}*/
uint16_t charging_current_adc;
void battery_pi_controller(void) {

	if((battery_pi.state == OFF) || (battery_pi.error == true) || (battery_pi.sticky_error == true)
			|| (is_pv_ready() == false))
	{

		stop_battery_charging(SLEEP_READY);
	}
	else if(battery_pi.error == true){
		stop_battery_charging(NO_SLEEP);
	}
	else {
		if(get_pwm_period() != BATT_CHARG_PI_PWM_PERIOD){
			set_pwm_period(BATT_CHARG_PI_PWM_PERIOD);
		}
			enable_pwm(BATT_CHARGING_PWM);
			select_adc_channel(BATT_CHARGING_ADC);
			do_adc_conversion();
			charging_current_adc = load_adc_result();
			update_pwm_duty_cycle(BATT_CHARGING_PWM, 0x57f);
			set_battery_charging_state(true);
	}
}

void charge_battery(void) 
{
	battery_pi.sleep_ready = false;
	battery_pi_controller();
}

static void stop_battery_charging(sleep_t sleep)
{
	disable_pwm(BATT_CHARGING_PWM);
	battery_pi_vars_init();
	update_pwm_duty_cycle(BATT_CHARGING_PWM, 0);
	enable_pwm(BATT_CHARGING_PWM);
	set_battery_charging_state(false);
	if(sleep == SLEEP_READY){
		battery_pi.sleep_ready = true;
	}else{
		battery_pi.sleep_ready = false;
	}
}

