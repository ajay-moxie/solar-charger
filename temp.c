#include "temp.h"
#include "led_load.h"
#include "battery_mgmt.h"
#include "PWM.h"


//main functions
battery_voltage_t battery_check;
void config_analog_pins(void) {
  ANSA0 = 1;
  LATA0 = 0;
  TRISA0 = 1;
  ANSA1 = 1;
  LATA1 = 0;
  TRISA1 = 1;
  ANSA4 = 1;
  LATA4 = 0;
  TRISA4 = 1;
  ANSB4 = 1;
  LATB4 = 0;
  TRISB4 = 1;
  ANSB5 = 1;
  LATB5 = 0;
  TRISB5 = 1;
  ANSC0 = 1;
  LATC0 = 0;
  TRISC0 = 1;
  ANSC2 = 1;
  LATC2 = 0;
  TRISC2 = 1;
  ANSC6 = 1;
  LATC6 = 0;
  TRISC6 = 1;
  ANSC7 = 1;
  LATC7 = 0;
  TRISC7 = 1;
}

void configure_adc(void) {
  //init_adc_var();
  config_analog_pins();
  config_adc();
}



void enable_tmr2_int(void) {
  clear_int_tmr2();
  enable_tmr2();
  TMR2IE = 1;
}

