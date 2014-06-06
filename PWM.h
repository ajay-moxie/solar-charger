#ifndef __PWM_H__
#define __PWM_H__
#include <htc.h>
#include <stdint.h>

typedef enum{
	PWM1,
	PWM2,
	PWM3,
	PWM4,
}pwm_id_t;

typedef enum{
	ACTIVE_HIGH,
	ACTIVE_LOW,
}pwm_polarity_t;

//10% Duty cycle
#define DUTY_CYCLE_10 00
#define DUTY_CYCLE_10_U ((DUTY_CYCLE_10 & 0xFC) >> 2)
#define DUTY_CYCLE_10_L ((DUTY_CYCLE_10 & 0x03) << 6)


//PWM functions
//void disable_pwm1(void);
//void enable_pwm1(void);
void update_pwm1_duty_cycle(uint16_t duty_cycle);
//void calculate_duty_cycle(void);
void init_pwm1_var(void);
void configure_pwm(void);
uint16_t get_pwm_period();
void set_pwm_period(uint16_t period);
void enable_pwm(pwm_id_t pwm_id);
void disable_pwm(pwm_id_t pwm_id);
void set_pwm_polarity(pwm_id_t pwm_id, pwm_polarity_t polarity);
void update_pwm_duty_cycle(pwm_id_t pwm_id, uint16_t duty_cycle);
void pwm_init(pwm_id_t pwm_id);

#endif

