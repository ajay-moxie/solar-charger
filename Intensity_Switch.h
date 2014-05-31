#ifndef __INTENSITY_SWITCH_H
#define __INTENSITY_SWITCH_H
#include <htc.h>
#include <stdint.h>
#include "common.h"


uint8_t switch1 = 0;

uint8_t sw_cnt_low = 0;
uint8_t sw_cnt_high = 0;

//function declaration
void config_int_switch1(void);
void detect_switch(void);
state_t check_switch_position(void);
#endif
