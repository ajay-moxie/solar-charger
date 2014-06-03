#include "temp.h"
#include "led_load.h"
#include "pi.h"
#include "interrupt.h"

struct pi led_load_pi;
void set_load_state(state_t state)
{
	DI();
	led_load_pi.state = state;
	EI();
}

void set_load_error(bool_t error)
{
	DI();
	led_load_pi.error = error;
	EI();
}

void set_load_sticky_error(bool_t error)
{
	DI();
	led_load_pi.sticky_error = error;
	EI();
}

void led_load_pi_init()
{
	led_load_pi.setpoint = LED_LOAD_SETPOINT;
	led_load_pi.pi_error = 0;
	led_load_pi.integral = 0;
	led_load_pi.duty_cycle = 0;
	led_load_pi.saturated = 0;
	led_load_pi.feedback = 0;

	led_load_pi.error = false;
	led_load_pi.sticky_error = false;
}
//main functions

load_regulation_t monitor_load_regulation(void) {
	uint8_t loop3;
	load_regulation_t return_val;
	uint16_t adc_int_val;

	load_vol = 0;
	return_val = OPEN_CKT_LOAD;
	adc_int_val = 0;

	select_adc_channel(LOAD_VOLTAGE);
	for (loop3=0; loop3<4; loop3++) {
		do_adc_conversion();
		adc_int_val = load_adc_result();
		load_vol = load_vol + adc_int_val;
	}
	load_vol = load_vol >> 2;
	load_vol = load_vol & 0x3FF;

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
}

void start_pwm1(void) {
	TMR2 = PWM_PERIOD;
	//Loading PR2 for 40KHz PWM
	PR2 = PWM_PERIOD;
	enable_load_switch();
	enable_pwm1();
}

void calculate_duty_cycle(void) {
	int16_t output;
	led_load_pi.pi_error = led_load_pi.setpoint - led_load_pi.feedback;

	if ((led_load_pi.pi_error > 1) || (led_load_pi.pi_error < -1)) {
		if (led_load_pi.saturated == 0) {
			if (led_load_pi.pi_error > 0) {
				if (led_load_pi.integral < INTEGRAL_MAX) {
					led_load_pi.integral = led_load_pi.integral + led_load_pi.pi_error;
				}
			}
			else {
				if (led_load_pi.integral > INTEGRAL_MIN) {
					led_load_pi.integral = led_load_pi.integral + led_load_pi.pi_error;
				}
			}
		}
		output = ((led_load_pi.pi_error * Kp) + (led_load_pi.integral * Ki));
		output = output / CONST_K;
		if (output > duty_max) {
			led_load_pi.saturated = 1;
			output = duty_max;
		}
		else if (output < 0) {
			led_load_pi.saturated = 1;
			output = duty_max;
		}
		else {
			led_load_pi.saturated = 0;
		}
	}
	led_load_pi.duty_cycle = (uint16_t) output;
}


void pi_controller(void) {
	load_regulation_t load_cond;

	if((led_load_pi.state == OFF) || (led_load_pi.error == true) || (led_load_pi.sticky_error == true)){
		/*
		   disable_load_switch();
		   disable_pwm1();*/
		//need to replace above two with load_disconnect
		load_disconnect();
	}
	else {
		load_cond = monitor_load_regulation();
		/*
		   if (load_cond == OPEN_CKT_LOAD) {
		   disable_load_switch();
		   disable_pwm1();
		   display_open_ckt_fault();
		   }
		   else*/ if (load_cond == SHORT_CKT_LOAD) {
			   disable_load_switch();
			   disable_pwm1();
			   display_short_ckt_fault();
		   }
		   else {
			   enable_load_switch();
			   enable_pwm1();
			   led_load_pi.feedback = led_load_pi.feedback + load_vol;
			   led_load_pi.feedback = led_load_pi.feedback >> 1;
			   calculate_duty_cycle();
			   update_pwm1_duty_cycle(led_load_pi.duty_cycle);
		   }
	}
}

void load_connect(void) {
	init_pwm4_var();
	if (first_run == 1) {
		first_run = 0;
		start_pwm1();
	}
	pi_controller();
}

void load_disconnect(void) {
	first_run = 1;
	disable_pwm1();
	disable_load_switch();
	init_pwm1_var();
}

