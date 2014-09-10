#include "pi.h"
#include "PWM.h"
	int32_t output1;
static void calculate_pi_duty_cycle(struct pi *pi_ptr) {
	pi_ptr->pi_error = pi_ptr->setpoint - pi_ptr->feedback;

	if ((pi_ptr->pi_error >= 1) || (pi_ptr->pi_error <= -1)) {
		if (pi_ptr->saturated == 0) {
			if (pi_ptr->pi_error > 0) {
				if (pi_ptr->integral < pi_ptr->integral_max) {
					pi_ptr->integral = pi_ptr->integral + pi_ptr->pi_error;
				}
			}
			else {
				if (pi_ptr->integral > pi_ptr->integral_min) {
					pi_ptr->integral = pi_ptr->integral + pi_ptr->pi_error;
				}
			}
		}
		output1 = ((pi_ptr->pi_error * pi_ptr->Kp) + (pi_ptr->integral * pi_ptr->Ki));
		output1 = output1 / pi_ptr->CONST_K;
		if (output1 > pi_ptr->duty_max) {
			pi_ptr->saturated = 1;
			output1 = pi_ptr->duty_max;
		}
		else if (output1 < 0) {
			//pi_ptr->saturated = 1;
			output1 = 0;
		}
		else {
			pi_ptr->saturated = 0;
		}
	}
	pi_ptr->duty_cycle = (uint16_t) output1;
}

void do_pi(struct pi *pi_ptr) {

	if((pi_ptr->state == OFF) || (pi_ptr->error == true) || (pi_ptr->sticky_error == true)){

		pi_ptr->stop_pi(SLEEP_READY);
	}
	else if(pi_ptr->error == true){ //not reachable, correct it
		pi_ptr->stop_pi(NO_SLEEP);
	}
	else {
		if(get_pwm_period() != pi_ptr->pi_pwm_period){
			set_pwm_period(pi_ptr->pi_pwm_period);
		}
			calculate_pi_duty_cycle(pi_ptr);
			update_pwm_duty_cycle(pi_ptr->pwm, pi_ptr->duty_cycle);
	}
}

