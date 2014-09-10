#include "common.h"
#include "config.h"
#include "pi.h"
#include "interrupt.h"
#include "pv_mgmt.h"
#include "PWM.h"
#include "battery_mgmt.h"

struct pi battery_pi;

void stop_battery_charging(sleep_t sleep);

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

void set_battery_pi_setpoint(uint16_t setpoint)
{
	battery_pi.setpoint = setpoint;
}
void set_battery_pi_sticky_error(bool_t error)
{
	DI();
	battery_pi.sticky_error = error;
	EI();
}

static battery_pi_vars_init()
{

	battery_pi.setpoint = BATT_CHARGING_SETPOINT;
	battery_pi.pi_error = 0;
	battery_pi.integral = 0;
	battery_pi.duty_cycle = 0;
	battery_pi.saturated = 0;
	battery_pi.feedback = 0;
	battery_pi.state = OFF;
	battery_pi.sense = BATT_CHARGING_SENSE;
	battery_pi.duty_max = BATT_CHARGING_DUTY_MAX;
	battery_pi.Kp = BATT_CHARGING_KP;
	battery_pi.Ki = BATT_CHARGING_KI;
	battery_pi.CONST_K= BATT_CHARGING_CONST_K;
	battery_pi.pi_pwm_period = BATT_CHARG_PI_PWM_PERIOD;
	battery_pi.pwm = BATT_CHARGING_PWM;
	battery_pi.integral_min = BATT_CHARGING_INTEGRAL_MIN;
	battery_pi.integral_max = BATT_CHARGING_INTEGRAL_MAX;
	select_adc_channel(BATT_CHARGING_ADC);
	do_adc_conversion();
	battery_pi.zero_ref = load_adc_result();
	if(battery_pi.sense == NEGATIVE){
		battery_pi.setpoint = battery_pi.zero_ref - battery_pi.setpoint;
	}
	//battery_pi.stop_pi = &stop_battery_charging;

}
void battery_pi_init()
{
	battery_pi_vars_init();
	battery_pi.error = false;
	battery_pi.sticky_error = false;
	battery_pi.sleep_ready = false;
}

void charge_battery(void) 
{
	battery_pi.sleep_ready = false;
	if((is_pv_ready() == false) || (battery_pi.state == OFF)){
		stop_battery_charging(SLEEP_READY);
	}
	else{
		if(get_charging_stage() == CC){
			select_adc_channel(BATT_CHARGING_ADC);
			do_adc_conversion();
			battery_pi.feedback = load_adc_result();
			if(battery_pi.sense == NEGATIVE){
				battery_pi.feedback = battery_pi.zero_ref - battery_pi.feedback;
			}
			else{
				battery_pi.feedback = battery_pi.feedback - battery_pi.zero_ref; //compensate for zero error
			}
		}
		else if(get_charging_stage()  == CV){
			battery_pi.feedback = get_battery_voltage();
		}
		do_pi(&battery_pi);
	}
}

void stop_battery_charging(sleep_t sleep)
{
	disable_pwm(BATT_CHARGING_PWM);
	battery_pi_vars_init();
	update_pwm_duty_cycle(BATT_CHARGING_PWM, 0);
	enable_pwm(BATT_CHARGING_PWM);
	set_battery_charging_state(OFF);
	if(sleep == SLEEP_READY){
		battery_pi.sleep_ready = true;
	}else{
		battery_pi.sleep_ready = false;
	}
}

