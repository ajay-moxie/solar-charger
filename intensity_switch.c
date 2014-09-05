
#include "intensity_switch.h"
#include "led_load.h"
#include "port.h"
#include "config.h"

static state_t intensity_switch;

static struct{
	uint8_t port;
	uint8_t pin;
	uint8_t intensity;
	uint8_t off_value;
}inten_switch_config[TOTAL_INTENSITY_SWITCH] = SWITCH;

void config_intensity_switch(void) {
	int i;
	for(i = 0; i < TOTAL_INTENSITY_SWITCH; i++){
		set_port_dir(inten_switch_config[i].port, inten_switch_config[i].pin, INPUT);
		set_port_type(inten_switch_config[i].port, inten_switch_config[i].pin, DIGITAL);
		set_port_interrupt(inten_switch_config[i].port, inten_switch_config[i].pin, RISING_EDGE);
		set_port_interrupt(inten_switch_config[i].port, inten_switch_config[i].pin, FALLING_EDGE);
	}
}

void check_initial_intensity_switch()
{
	uint8_t sw;
	int i;
	intensity_switch = OFF;
	for(i = 0; i < TOTAL_INTENSITY_SWITCH; i++){
		sw = read_port_pin(inten_switch_config[i].port,inten_switch_config[i].pin);
		if (inten_switch_config[i].off_value != sw) {
			intensity_switch = ON;
			led_load_pi_init();
			set_led_load_pi_setpoint(inten_switch_config[i].intensity);
		}
	}
}
void detect_intensity_switch(void)
{
	uint8_t sw;
	int i;
	for(i = 0; i < TOTAL_INTENSITY_SWITCH; i++){
		if(read_clear_port_interrupt(inten_switch_config[i].port, inten_switch_config[i].pin)){
			sw = read_port_pin(inten_switch_config[i].port,inten_switch_config[i].pin);
			if (inten_switch_config[i].off_value != sw) {
				intensity_switch = ON;
				led_load_pi_init();
				set_led_load_pi_setpoint(inten_switch_config[i].intensity);
			}
			else {
				intensity_switch = OFF;
			}
		}
	}
}

state_t intensity_switch_position(void) {

	return intensity_switch;
}


