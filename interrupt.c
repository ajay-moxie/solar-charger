
#include "interrupt.h"
#include "led_load.h"
#include "battery_pi.h"
#include "mobile_pi.h"
#include "intensity_switch.h"
#include "battery_mgmt.h"

static int charger_load_switch;

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

void EI()
{
	GIE = 1;
}

void DI()
{
	GIE = 0;
}

void interrupt update_intensity_flags_int(void) {
	//Check intensity switch position and set
	//flags accordingly
	detect_intensity_switch();
	if (TMR2IF == 1) {
		charger_load_switch = (charger_load_switch + 1);
		if((charger_load_switch % 3) == 0)
			load_connect();
		if((charger_load_switch % 3) == 1)
			charge_mobile();
		else{
			charge_battery();
		}
		TMR2IF = 0;
	}
}

void configure_interrupt(void) {
	disable_IOC_interrupt();
	enable_IOC_interrupt();
}
