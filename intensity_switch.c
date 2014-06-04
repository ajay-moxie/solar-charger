
#include "intensity_switch.h"
#include "led_load.h"

static state_t intensity_switch;


void config_intensity_switch(void) {
	TRISA5 = 1;
	ANSELA = ANSELA & (~(0x20));
	//intensity switch1
	//Configure falling edge interrupt for RA5
	IOCAN5 = 1;
	//Configure rising edge interrupt for RA5
	IOCAP5 = 1;
}

void detect_intensity_switch(void)
{
	int sw;
	sw = RA5;
	if (sw == 0) {
		intensity_switch = ON;
		led_load_pi_init();
	} else {
		intensity_switch = OFF;
	}
}

state_t intensity_switch_position(void) {

	return intensity_switch;
}


