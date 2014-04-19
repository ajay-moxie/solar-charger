
#include "Intensity_Switch.h"

void enable_IOC_interrupt(void) {
  //Enable global interrupt bit
  GIE = 1;
  //Enable interrupt on change bit
  IOCIE = 1;
}

void disable_IOC_interrupt(void) {
  //Disable interrupt on change bit
  IOCIE = 0;
}

void config_int_switch1(void) {
  //intensity switch1
  //Configure falling edge interrupt for PWM
  IOCAN5 = 1;
  //Configure rising edge interrupt for PWM
  IOCAP5 = 1;
}

void detect_switch(void) {
  uint8_t cnt;


  for (cnt=0; cnt<5; cnt++) {
    if (RA5 == 0) {
      sw_cnt_high = 0;
      sw_cnt_low = sw_cnt_low + 1;
    }
    else {
      sw_cnt_low = 0;
      sw_cnt_high = sw_cnt_high + 1;
    }
  }
  if (sw_cnt_low > 3) {
    switch1 = 1;
  }
  if (sw_cnt_high > 3) {
    switch1 = 0;
  }
}

switch_position_t check_switch_position(void) {
  switch_position_t return_val;

  return_val = OFF;

  sw_cnt_low = 0;
  sw_cnt_high = 0;
  detect_switch();
  if (switch1 == 1) {
    return_val = ON;
  }
  else {
    return_val = OFF;
  }

  return return_val;
}

void interrupt update_intensity_flags_int(void) {
  //Check intensity switch position and set
  //flags accordingly
  IOCAF5 = 0;
  if (TMR2IF == 1) {
    start_pi = 1;
    TMR2IF = 0;
  }
}

void configure_interrupt(void) {
  disable_IOC_interrupt();
  config_int_switch1();
  enable_IOC_interrupt();
}
