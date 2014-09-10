#include "common.h"
#include "config.h"
#include "pv_mgmt.h"
#include "interrupt.h"
#include "ADC.h"

static bool_t pv_ready;
static uint16_t pv1_volt;

measure_pv_voltage()
{
	DI();
	select_adc_channel(CHARGER_ADC_LINE);
	do_adc_conversion();
	pv1_volt = load_adc_result();
	EI();
}
uint16_t aa;
uint16_t get_pv_voltage()
{
	uint8_t calc_volt;
	DI();
#ifdef PV_NEGATIVE_SIDE
	if((pv1_volt > PV_BASE_VOLT_LOW) && (pv1_volt < PV_BASE_VOLT_HI))
		calc_volt = 0;
	else if(pv1_volt > PV_BASE_VOLT_HI){
		//error
	}else{
		pv1_volt = PV_BASE_VOLT_LOW - pv1_volt;
	}
#endif
#ifdef PV_POSITIVE_SIDE
	calc_volt = pv1_volt - PV_BASE_VOLT_LOW;
#endif
	EI();
	return calc_volt;
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
