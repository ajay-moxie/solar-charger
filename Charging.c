
#include "Charging.h"

void init_pwm4_var(void) {
  charger_Kp = CHARGER_KP;
  charger_Ki = CHARGER_KI;
  charger_duty_max = CHARGER_DUTY_MAX;
  charger_setpoint = CHARGER_SETPOINT;
  charger_feedback = 0;
  charger_error = 0;
  charger_integral = 0;
  charger_duty_cycle = 0;
  charger_saturated = 0;
  PWM4POL = 1;
}

void init_CV_var(void) {
  charger_setpoint = BATT_CV_VOL;
  charger_feedback = 0;
  charger_error = 0;
  charger_integral = 0;
  charger_duty_cycle = 0;
  charger_saturated = 0;
  PWM4POL = 0;
}

void config_pwm4(void) {
  //Clear PWM4CON
  PWM4CON = 0x0;
  //Set PWM period
  //PR2 = CHARGER_PWM_PERIOD;
  //Setting duty cycle to 10%
  PWM4DCH = CHARGER_DUTY_CYC_10_U;
  PWM4DCL = CHARGER_DUTY_CYC_10_L;
  //PWM enable
  PWM4EN = 1;
  PWM4OUT = 0;
  PWM4POL = 1;
}

void update_pwm4_duty_cycle(uint16_t duty_cyc) {

  //Setting duty cycle
  PWM4DCH = (duty_cyc & 0x3FC) >> 2;
  PWM4DCL = (duty_cyc & 0x03) << 6;
}

void disable_charging(void) {
  //Disable PWM output
  PWM4OE = 0;
}

void enable_charging(void) {
  //Enable PWM output
  PWM4OE = 1;
}

void calc_charger_duty_cycle(void) {
  int16_t charger_out;

  if (start_CV_stage == 0) {
    charger_error = charger_feedback - charger_setpoint;
  }
  else {
    charger_error = charger_setpoint - charger_feedback;
  }

  if ((charger_error > 1) || (charger_error < -1)) {
    if (charger_saturated == 0) {
      if (charger_error > 0) {
        if (charger_integral < CHARGER_INTEGRAL_MAX)
          charger_integral = charger_integral + charger_error; 
        }
      else {
        if (charger_integral > CHARGER_INTEGRAL_MIN)
          charger_integral = charger_integral + charger_error;
      }
    }
    charger_out = ((charger_error * charger_Kp) + (charger_integral * charger_Ki));
    charger_out = charger_out / CHARGER_CONST_K;
    /*
    if (charger_out > charger_duty_max) {
      charger_saturated = 1;
      charger_out = charger_duty_max;
    }
    else if (charger_out < 0) {
      charger_saturated = 1;
      charger_out = charger_duty_max;
    }
    else {
      charger_saturated = 0;
    }
    */
  }
  charger_duty_cycle = (uint16_t) charger_out;
}

void configure_charger(void) {
  LATC1 = 0;
  TRISC1 = 0;
  start_CV_stage = 0;
  start_charging = 0;
  init_pwm4_var();
  disable_charging();
  config_pwm4();
}

void reset_charger_config(void) {
  start_CV_stage = 0;
  init_pwm4_var();
}

void charging_stop(void) {
  start_charging = 0;
  disable_charging();
  reset_charger_config();
}
