#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__
#include <htc.h>
#include <stdint.h>

typedef enum{
	RISING_EDGE,
	FALLING_EDGE,
}interrupt_type_t;
//function declaration
void enable_IOC_interrupt(void);
void disable_IOC_interrupt(void);

void interrupt update_intensity_flags_int(void);
void configure_interrupt(void);
void DI();
void EI();
#endif
