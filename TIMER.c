
#include "TIMER.h"

void config_tmr2(void) {
  //Keep timer off
  TMR2ON = 0;
  //Set timer period
  TMR2 = TMR2_PERIOD;
  //Set output prescalar to 1:10
  TOUTPS0 = 1;
  TOUTPS1 = 0;
  TOUTPS2 = 0;
  TOUTPS3 = 1;
  //Set timer clock prescalar to 1:1
  T2CKPS0 = 0;
  T2CKPS1 = 0;
}

void enable_tmr2(void) {
  //Start timer
  TMR2ON = 1;
}

void disable_tmr2(void) {
  //Stop timer
  TMR2ON = 0;
}

void clear_int_tmr2(void) {
  //Clearing interrupt
  TMR2IF = 0;
}

void wait_for_int_tmr2(void) {
  //Wait for interrupt to occur
  while(TMR2IF == 0);
}

void config_tmr1(void) {
  TMR1GE = 0;
  TMR1ON = 0;
  //select timer1 clock
  TMR1CS0 = 0;
  TMR1CS1 = 0;
  //select 1:1 prescalar
  T1CKPS0 = 0;
  T1CKPS1 = 0;
  //configure for 1ms period
  TMR1H = 0x00;
  TMR1L = 0x00;
  nT1SYNC = 1;
}


void enable_tmr1() {
  TMR1ON = 1;
}

void disable_tmr1() {
  TMR1ON = 0;
}

void clear_int_tmr1() {
  TMR1IF = 0;
}

void wait_for_int_tmr1() {
  while(TMR1IF == 0);
}

void delay_loop_nms(uint8_t ms_val) {
  uint8_t i;
 
  for (i=0; i<ms_val; i++) {
    TMR1H = 0xF0;
    TMR1L = 0x60;
    TMR1ON = 1;
    while(TMR1IF == 0);
    TMR1IF = 0;
    TMR1ON = 0;
  } 
}

void delay_loop_ns(uint8_t t_sec) {
  uint8_t i;
  uint8_t j;
  
  TMR1H = 0x00;
  TMR1L = 0x00;
  TMR1ON = 1;
  for (i=0; i<t_sec; i++) {
    for (j=0; j<62; j++) {
      while(TMR1IF == 0);
      TMR1IF = 0;
    }
  }
  TMR1ON = 0;
}

void configure_timer(void) {
  disable_tmr1();
  config_tmr2();
  config_tmr1();
  clear_int_tmr2();
  clear_int_tmr1();
}
