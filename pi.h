#ifndef __PI_H__
#define __PI_H__
#include "common.h"

struct pi{
	uint8_t Kp;
	uint8_t Ki;
	uint16_t duty_max;
	uint16_t setpoint;
	uint16_t feedback;
	int16_t error;
	int16_t integral;
	uint16_t duty_cycle;
	uint8_t saturated;
	state_t state;
};
#endif
