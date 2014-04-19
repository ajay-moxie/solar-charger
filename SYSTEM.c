
#include "SYSTEM.h"

void select_internal_lp_osc(void) {
  //Select 31KHz internal low power osc
  IRCF0 = 0;
  IRCF1 = 0;
  IRCF2 = 0;
  IRCF3 = 0;
}

void select_internal_hp_osc(void) {
  //Select 16MHz internal high power osc
  IRCF0 = 1;
  IRCF1 = 1;
  IRCF2 = 1;
  IRCF3 = 1;
}

void select_internal_osc(void) {
  //Selecting internal oscillator as system clock
  SCS1 = 1; 
}

void wait_for_hp_osc_ready(void) {
  //Wait for high freq osc ready
  while(HFIOFR == 1);
}

void wait_for_lp_osc_ready(void) {
  //Wait for low power osc ready
  while(LFIOFR == 1);
}

void wait_for_hp_osc_stable(void) {
  //Wait for high freq osc to become stable
  while(HFIOFS == 1);
}

void config_digital_pins(void) {
  TRISA5 = 1;
  TRISB7 = 1;
  LATB6 = 1;
  LATC4 = 1;
  TRISB6 = 0;
  TRISC4 = 0;
}

void enter_sleep_mode(void) {
  asm("sleep");
}

void fvr_enable(void) {
  //Enable Fixed Voltage Reference
  FVREN = 1;
}

void fvr_disable(void) {
  //Disable Fixed Voltage Reference
  FVREN = 0;
}

void config_fvr(void) {
  //Select 2.048V for ADC reference
  ADFVR1 = 1;
  ADFVR0 = 0;
}

void sel_sys_clk_int_osc(void) {
  select_internal_hp_osc();
  select_internal_osc();
  config_digital_pins();
  fvr_disable();
  config_fvr();
  fvr_enable();
}
