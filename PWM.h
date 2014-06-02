
#include <htc.h>
#include <stdint.h>


//PWM period for 40KHz PWM output
#define PWM_PERIOD 100

//10% Duty cycle
#define DUTY_CYCLE_10 40
#define DUTY_CYCLE_10_U ((DUTY_CYCLE_10 & 0xFC) >> 2)
#define DUTY_CYCLE_10_L ((DUTY_CYCLE_10 & 0x03) << 6)

//PI defines
#define KP 16
#define KI 2
#define DUTY_MAX 350  //87.5% duty cycle
#define SETPOINT 68  //130 mV
#define INTEGRAL_MIN -32000
#define INTEGRAL_MAX 32000
#define CONST_K 64

uint8_t Kp;
uint8_t Ki;
uint16_t duty_max;
uint16_t setpoint;
uint16_t feedback;
int16_t error;
int16_t integral;
uint16_t duty_cycle;
uint8_t saturated;

//PWM functions
void disable_pwm1(void);
void enable_pwm1(void);
void update_pwm1_duty_cycle(uint16_t duty_cycle);
void init_pwm1_var(void);
void configure_pwm(void);
