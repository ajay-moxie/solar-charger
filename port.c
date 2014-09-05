#include "port.h"
#include "interrupt.h"
set_port_dir(port_t port, uint8_t pin_no, port_dir_t dir)
{
	volatile uint8_t *reg;

	if(port == PORT_A)
		reg = &TRISA;
	else if(port == PORT_B)
		reg = &TRISB;
	else if(port == PORT_C)
		reg = &TRISC;

	if(dir == OUTPUT)
		(*reg) &= ~(1 << pin_no);
	if(dir == INPUT)
		(*reg) |= (1 << pin_no);
}

set_port_type(port_t port, uint8_t pin_no, port_type_t type)
{
	volatile uint8_t *reg;

	if(port == PORT_A)
		reg = &ANSELA;
	else if(port == PORT_B)
		reg = &ANSELB;
	else if(port == PORT_C)
		reg = &ANSELC;

	if(type == DIGITAL)
		(*reg) &= ~(1 << pin_no);
	if(type == ANALOG)
		(*reg) |= (1 << pin_no);
}

set_port_interrupt(port_t port, uint8_t pin_no, interrupt_type_t type)
{
	volatile uint8_t *reg;

	if((port == PORT_A) && (type == RISING_EDGE))
		reg = &IOCAP;
	else if((port == PORT_A) && (type == FALLING_EDGE))
		reg = &IOCAN;
	if((port == PORT_B) && (type == RISING_EDGE))
		reg = &IOCBP;
	else if((port == PORT_B) && (type == FALLING_EDGE))
		reg = &IOCBN;

	(*reg) |= (1 << pin_no);

}

uint8_t read_port_pin(port_t port, uint8_t pin)
{
	volatile uint8_t *reg;

	if(port == PORT_A)
		reg = &PORTA;
	else if(port == PORT_B)
		reg = &PORTB;
	else if(port == PORT_C)
		reg = &PORTC;

	return ((*reg) & (1 << pin)) >> pin;
}

uint8_t read_clear_port_interrupt(port_t port, uint8_t pin)
{
	volatile uint8_t *reg;
	uint8_t val;

	if(port == PORT_A)
		reg = &IOCAF;
	else if(port == PORT_B)
		reg = &IOCBF;

	val = ((*reg) & (1 << pin)) >> pin;
	if(val)
		(*reg) &= ~(1 << pin);
//	return ((*reg) & (1 << pin)) >> pin;
	return val;
}
