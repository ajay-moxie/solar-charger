
#include "temp.h"
#include "led_load.h"
#include "interrupt.h"
#include "pi.h"
#include "battery_mgmt.h"
#include "load_mgmt.h"
#include "common.h"
#include "intensity_switch.h"
#include "power_mgmt.h"
//#define TEST_LOAD_ON_OFF
#ifdef TEST_LOAD_ON_OFF
uint16_t test = 0;
#endif
//Setting configuration word1
__CONFIG(FOSC_INTOSC & BOREN_OFF & WDTE_OFF & CP_OFF & CLKOUTEN_OFF & PWRTE_OFF & MCLRE_ON);
//Setting configuration word2
__CONFIG(STVREN_ON & LVP_OFF);

uint16_t count_10sec;
uint8_t start_150ms;
state_t load_switch_state = ON;
state_t PV_state = OFF;
//battery_voltage_t battery_check;

//uint16_t bat[50];
int main(void) {
	uint16_t batt_volt;
	int i = 0;
	ovp_mon_t ovp_cond;

	charging_stage_t temp;

	sel_sys_clk_int_osc();
    	sleep_init();
	configure_interrupt();
	config_intensity_switch();
	configure_adc();
	configure_timer();
	load_mgmt_init();
	load_switch_init();
	config_LED_port();
	configure_charger();
	led_load_pi_init();
	init_vars();
	PEIE = 1;
	enable_tmr2_int();
	count_10sec = 0;
	start_150ms = 0;
	delay_loop_nms(5);
    DI();
	detect_intensity_switch();
    EI();
	while(1) {

		if((intensity_switch_position() == ON) && (PV_state == OFF)){
			set_load_state(ON);
		
			load_mgmt();
		}
		else if(PV_state == ON){
			//manage battery changing
		}
		else{
			set_load_state(OFF);
#ifdef POWER_MGMT
			DI();
			if(load_power_state() == SLEEP_READY){
				power_save();
			}
			EI();
#endif
		}
#ifdef TEST_LOAD_ON_OFF
		test++;
		if(test == 5000)
			set_load_state(PI_OFF);
		if(test == 10000){
			set_load_state(PI_ON);
			test = 0;
		}
#endif
	}
	return 0;
}
