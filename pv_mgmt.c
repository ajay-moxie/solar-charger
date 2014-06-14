#include "common.h"
#include "config.h"
#include "pv_mgmt.h"
#include "interrupt.h"
#include "ADC.h"

static bool_t pv_ready;
uint16_t aa;
uint16_t get_pv_voltage()
{
	uint16_t pv_volt;
	DI();
	select_adc_channel(CHARGER_ADC_LINE);
	do_adc_conversion();
	pv_volt = load_adc_result();
	aa = pv_volt;
	if((pv_volt > PV_BASE_VOLT_LOW) && (pv_volt < PV_BASE_VOLT_HI))
		pv_volt = 0;
	else if(pv_volt > PV_BASE_VOLT_HI){
		//error
	}else{
		pv_volt = PV_BASE_VOLT_LOW - pv_volt;
	}
	EI();
	return pv_volt;
}

void set_pv_ready(bool_t state)
{
	pv_ready = state;
}

bool_t is_pv_ready()
{
	return pv_ready;
}

void pv_init()
{
	pv_ready = false;
}
