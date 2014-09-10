#ifndef __PI_H__
#define __PI_H__
#include "common.h"

struct pi{
	uint8_t Kp;
	uint8_t Ki;
	uint16_t pi_pwm_period;
	uint16_t duty_max;
	uint16_t setpoint;
	uint16_t feedback;
	uint16_t zero_ref;
	int16_t pi_error;
	int16_t integral;
	int16_t integral_min;
	int16_t integral_max;
	uint16_t duty_cycle;
	uint8_t saturated;
	uint8_t pwm;
	uint8_t CONST_K;
	state_t state;
	sense_t sense;
	bool_t error;
	bool_t sticky_error;
	bool_t sleep_ready;
	void (*stop_pi)(sleep_t sleep);
};

void do_pi(struct pi *pi_ptr);
#endif
