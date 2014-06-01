#ifndef __INTENSITY_SWITCH_H
#define __INTENSITY_SWITCH_H
#include <htc.h>
#include <stdint.h>
#include "common.h"

//function declaration
void config_intensity_switch(void);
state_t intensity_switch_position(void);
void detect_intensity_switch(void);
#endif
