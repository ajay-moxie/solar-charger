
#include "PWM.h"

uint16_t get_pwm_period()
{
	return PR2;
}

void set_pwm_period(uint16_t period)
{
	PR2 = period;
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


void configure_pwm(void) {
  LATC5 = 1;
  TRISC5 = 0;
  disable_pwm1();
  config_pwm1();
}
