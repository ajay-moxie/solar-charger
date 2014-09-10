#include "config.h"
#include "battery_mgmt.h"
#include "battery_pi.h"
#include "pv_mgmt.h"
#include "interrupt.h"

void verify_charger()
{
	uint16_t pv_volt;
	uint16_t batt_volt;
	pv_volt = get_pv_voltage();
	batt_volt = get_battery_voltage();
//DI();
	if(VERIFY_CHARGER(pv_volt, batt_volt)){
		set_pv_ready(true);
		if(battery_charging_state() == OFF){
			if(battery_charging_needed() == true){
				set_battery_pi_state(ON);
				set_battery_charging_state(ON);
			}
		}
	}else{
		set_pv_ready(false);
		set_battery_pi_state(OFF);
		set_battery_charging_state(OFF);
	}
//EI();
}
