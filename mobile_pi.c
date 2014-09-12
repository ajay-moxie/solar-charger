#include "common.h"
#include "config.h"
#include "pi.h"
#include "interrupt.h"
#include "pv_mgmt.h"
#include "PWM.h"
#include "mobile_mgmt.h"
#include "ADC.h"

struct pi mobile_pi;

void stop_mobile_charging(sleep_t sleep);

sleep_t mobile_pi_power_state()
{
	return mobile_pi.sleep_ready;
}
void set_mobile_pi_state(state_t state)
{
	DI();
	mobile_pi.state = state;
	EI();
}

void set_mobile_pi_error(bool_t error)
{
	DI();
	mobile_pi.error = error;
	EI();
}

void set_mobile_pi_setpoint(uint16_t setpoint)
{
	mobile_pi.setpoint = setpoint;
}
void set_mobile_pi_sticky_error(bool_t error)
{
	DI();
	mobile_pi.sticky_error = error;
	EI();
}

static mobile_pi_vars_init()
{

	mobile_pi.setpoint = MOBILE_CHARGING_SETPOINT;
	mobile_pi.pi_error = 0;
	mobile_pi.integral = 0;
	mobile_pi.duty_cycle = 0;
	mobile_pi.saturated = 0;
	mobile_pi.feedback = 0;
	mobile_pi.state = ON;
	mobile_pi.sense = MOBILE_CHARGING_SENSE;
	mobile_pi.duty_max = MOBILE_CHARGING_DUTY_MAX;
	mobile_pi.Kp = MOBILE_CHARGING_KP;
	mobile_pi.Ki = MOBILE_CHARGING_KI;
	mobile_pi.CONST_K= MOBILE_CHARGING_CONST_K;
	mobile_pi.pi_pwm_period = MOBILE_CHARGING_PI_PWM_PERIOD;
	mobile_pi.pwm = MOBILE_CHARGING_PWM;
	mobile_pi.integral_min = MOBILE_CHARGING_INTEGRAL_MIN;
	mobile_pi.integral_max = MOBILE_CHARGING_INTEGRAL_MAX;
	select_adc_channel(MOBILE_CHARGING_VOLTAGE_SENSE_ADC);
	do_adc_conversion();
	mobile_pi.zero_ref = load_adc_result();
	if(mobile_pi.sense == NEGATIVE){
		mobile_pi.setpoint = mobile_pi.zero_ref - mobile_pi.setpoint;
	}
	mobile_pi.stop_pi = stop_mobile_charging;

}
void mobile_pi_init()
{
	mobile_pi_vars_init();
	mobile_pi.error = false;
	mobile_pi.sticky_error = false;
	mobile_pi.sleep_ready = false;
}

void charge_mobile(void) 
{
	mobile_pi.sleep_ready = false;
	if(mobile_pi.state == OFF){
		stop_mobile_charging(SLEEP_READY);
	}
	else{
		select_adc_channel(MOBILE_CHARGING_VOLTAGE_SENSE_ADC);
		do_adc_conversion();
		mobile_pi.feedback = load_adc_result();
		do_pi(&mobile_pi);
	}
}

void stop_mobile_charging(sleep_t sleep)
{
	disable_pwm(MOBILE_CHARGING_PWM);
	mobile_pi_vars_init();
	update_pwm_duty_cycle(MOBILE_CHARGING_PWM, 0);
	enable_pwm(MOBILE_CHARGING_PWM);
	set_mobile_charging_state(OFF);
	if(sleep == SLEEP_READY){
		mobile_pi.sleep_ready = true;
	}else{
		mobile_pi.sleep_ready = false;
	}
}

