#ifndef __PORT_H__
#define __PORT_H__
#include "interrupt.h"
typedef enum{
	PORT_A,
	PORT_B,
	PORT_C,
}port_t;

typedef enum{
	PORTA_0 = 0,
	PORTA_1 = 1,
	PORTA_2 = 2,
	PORTA_3 = 3,
	PORTA_4 = 4,
	PORTA_5 = 5,
}porta_pin_t;

typedef enum{
	PORTB_5,
	PORTB_6,
	PORTB_7,
}portb_pin_t;

typedef enum{
	PORTC_0,
	PORTC_1,
	PORTC_2,
	PORTC_3,
	PORTC_4,
	PORTC_5,
	PORTC_6,
	PORTC_7,
} portc_pin_t;

typedef enum{
	OUTPUT,
	INPUT,
}port_dir_t;

typedef enum{
	DIGITAL,
	ANALOG,
}port_type_t;

set_port_dir(port_t port, uint8_t pin_no, port_dir_t dir);
set_port_type(port_t port, uint8_t pin_no, port_type_t type);
set_port_interrupt(port_t port, uint8_t pin_no, interrupt_type_t type);
uint8_t read_port_pin(port_t port, uint8_t pin);
uint8_t read_clear_port_interrupt(port_t port, uint8_t pin);
#endif
