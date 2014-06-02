
#include "PWM.h"

void init_pwm1_var(void) {
  Kp = KP;
  Ki = KI;
  duty_max = DUTY_MAX;
  setpoint = SETPOINT;
  feedback = 0;
  error = 0;
  integral = 0;
  duty_cycle = 0;
  saturated = 0;
}

void config_pwm1(void) {
  //Clear PWM1CON
  PWM1CON = 0x0;
  //Set PWM period
  PR2 = PWM_PERIOD;
  //Setting duty cycle to 10%
  PWM1DCH = DUTY_CYCLE_10_U;
  PWM1DCL = DUTY_CYCLE_10_L;
  //PWM enable
  PWM1EN = 1;
  PWM1OUT = 0;
  PWM1POL = 1;
}

void disable_pwm1(void) {
  //Disabling output pin
  PWM1OE = 0;
}

void enable_pwm1(void) {
  //Enabling output pin
  PWM1OE = 1;
}

void update_pwm1_duty_cycle(uint16_t duty_cyc) {

  //Setting duty cycle
  PWM1DCH = (duty_cyc & 0x1FC) >> 2;
  PWM1DCL = (duty_cyc & 0x03) << 6;
}

/*
void calculate_duty_cycle(void) {
  int16_t output;

  error = setpoint - feedback;

  if ((error > 1) || (error < -1)) {
    if (saturated == 0) {
      if (error > 0) {
        if (integral < INTEGRAL_MAX) {
          integral = integral + error;
	}
      }
      else {
        if (integral > INTEGRAL_MIN) {
          integral = integral + error;
	}
      }
    }
    output = ((error * Kp) + (integral * Ki));
    output = output / CONST_K;
    if (output > duty_max) {
      saturated = 1;
      output = duty_max;
    }
    else if (output < 0) {
      saturated = 1;
      output = duty_max;
    }
    else {
      saturated = 0;
    }
  }
  duty_cycle = (uint16_t) output;
}
*/

void configure_pwm(void) {
  LATC5 = 1;
  TRISC5 = 0;
  init_pwm1_var();
  disable_pwm1();
  config_pwm1();
}
