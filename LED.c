
#include "LED.h"

void config_LED_port(void) {
  LATB6 = 1;
  LATC4 = 1;
  TRISB6 = 0;
  TRISC4 = 0;
  display_flag = 0;
  led_cnt = 0;
}

void disable_green_LED(void) {
  LATC4 = 1;
}

void enable_green_LED(void) {
  LATC4 = 0;
}

void disable_red_LED(void) {
  LATB6 = 1;
}

void enable_red_LED(void) {
  LATB6 = 0;
}

void display_ovp_fault(void) {
  
  led_cnt = led_cnt + 1;
  if (led_cnt == OVP_FAULT_DELAY) {
    display_flag = ~display_flag;
    led_cnt = 0;
  }
  if (display_flag) {
    enable_red_LED();
    enable_green_LED();
  }
  else {
    disable_red_LED();
    disable_green_LED();
  }
}

void display_bat_low(void) {
  uint8_t i;

  for (i=0; i<5; i++) {
    enable_red_LED();
    delay_loop_nms(200);
    disable_red_LED();
    delay_loop_nms(200);
  }
}

void display_open_ckt_fault(void) {

  led_cnt = led_cnt + 1;
  if (led_cnt == OPEN_CKT_FAULT_DELAY) {
    display_flag = ~display_flag;
    led_cnt = 0;
  }
  if (display_flag) {
    enable_red_LED();
    disable_green_LED();
  }
  else {
    disable_red_LED();
    enable_green_LED();
  }
}

void display_short_ckt_fault(void) {

  led_cnt = led_cnt + 1;
  if (led_cnt == SHORT_CKT_FAULT_DELAY) {
    display_flag = ~display_flag;
    led_cnt = 0;
  }
  if (display_flag) {
    enable_green_LED();
    disable_red_LED();
  }
  else {
    enable_red_LED();
    disable_green_LED();
  }
}

void display_CC_stage(void) {

  led_cnt = led_cnt + 1;
  if (led_cnt == CC_STAGE_DELAY) {
    display_flag = ~display_flag;
    led_cnt = 0;
  }
  if (display_flag) {
    enable_green_LED();
    disable_red_LED();
  }
  else {
    disable_red_LED();
    disable_green_LED();
  }
}

void display_CV_stage(void) {

  led_cnt = led_cnt + 1;
  if (led_cnt == CV_STAGE_DELAY) {
    display_flag = ~display_flag;
    led_cnt = 0;
  }
  if (display_flag) {
    enable_green_LED();
    disable_red_LED();
  }
  else {
    disable_red_LED();
    disable_green_LED();
  }
}

void blink_red_led(void) {

  led_cnt = led_cnt + 1;
  if (led_cnt == RED_LED_BLINK_DELAY) {
    display_flag = ~display_flag;
    led_cnt = 0;
  }
  if (display_flag) {
    enable_red_LED();
    disable_green_LED();
  }
  else {
    disable_red_LED();
    disable_green_LED();
  }
}

void blink_green_led(void) {

  led_cnt = led_cnt + 1;
  if (led_cnt == GREEN_LED_BLINK_DELAY) {
    display_flag = ~display_flag;
    led_cnt = 0;
  }
  if (display_flag) {
    enable_green_LED();
    disable_red_LED();
  }
  else {
    disable_red_LED();
    disable_green_LED();
  }
}
