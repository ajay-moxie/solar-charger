#include "config.h"
#include "PWM.h"

uint16_t get_pwm_period()
{
	return PR2;
}

void set_pwm_period(uint16_t period)
{
	PR2 = period;
}

void set_pwm_polarity(pwm_id_t pwm_id, pwm_polarity_t polarity)
{
	switch(pwm_id){
	case PWM1:
		PWM1POL = polarity;
		break;
	case PWM2:
		PWM2POL = polarity;
		break;
	case PWM3:
		PWM3POL = polarity;
		break;
	case PWM4:
		PWM4POL = polarity;
		break;
	default:
		break;
	}
}

void enable_pwm(pwm_id_t pwm_id)
{
	switch(pwm_id){
	case PWM1:
		PWM1OE = 1;
		break;
	case PWM2:
		PWM2OE = 1;
		break;
	case PWM3:
		PWM3OE = 1;
		break;
	case PWM4:
		PWM4OE = 1;
		break;
	default:
		break;
	}
}

void disable_pwm(pwm_id_t pwm_id)
{
	switch(pwm_id){
	case PWM1:
		PWM1OE = 0;
		break;
	case PWM2:
		PWM2OE = 0;
		break;
	case PWM3:
		PWM3OE = 0;
		break;
	case PWM4:
		PWM4OE = 0;
		break;
	default:
		break;
	}
}

void update_pwm_duty_cycle(pwm_id_t pwm_id, uint16_t duty_cycle)
{
	switch(pwm_id){
	case PWM1:
  		PWM1DCH = (duty_cycle & 0x1FC) >> 2;
		PWM1DCL = (duty_cycle & 0x03) << 6;
		break;
	case PWM2:
  		PWM2DCH = (duty_cycle & 0x1FC) >> 2;
		PWM2DCL = (duty_cycle & 0x03) << 6;
		break;
	case PWM3:
  		PWM3DCH = (duty_cycle & 0x1FC) >> 2;
		PWM3DCL = (duty_cycle & 0x03) << 6;
		break;
	case PWM4:
  		PWM4DCH = (duty_cycle & 0x1FC) >> 2;
		PWM4DCL = (duty_cycle & 0x03) << 6;
		PWM4OE = 0;
		break;
	default:
		break;
	}
}

void config_pwm1(void) {
  //Clear PWM1CON
  PWM1CON = 0x0;
  //Set PWM period
  PR2 = LED_LOAD_PI_PWM_PERIOD;
  //Setting duty cycle to 10%
  update_pwm_duty_cycle(PWM1, 0);
  //PWM enable
  PWM1EN = 1;
  PWM1OUT = 0;
  set_pwm_polarity(PWM1, ACTIVE_LOW);
}


/*void update_pwm1_duty_cycle(uint16_t duty_cyc) {

  //Setting duty cycle
  PWM1DCH = (duty_cyc & 0x1FC) >> 2;
  PWM1DCL = (duty_cyc & 0x03) << 6;
}*/


void pwm_init(pwm_id_t pwm_id)
{
	switch(pwm_id){
	case PWM1:
		TRISC5 = 0;//configured as o/p
		PWM1CON = 0x0;
		PWM1EN = 1;
		disable_pwm(PWM1);
		break;
	case PWM2:
		TRISC3 = 0;//configured as o/p
		PWM3CON = 0x0;
		PWM3EN = 1;
		disable_pwm(PWM2);
		break;
	case PWM3:
		break;
	case PWM4:
		break;
	default:
		break;
	}
}
