
#include "interrupt.h"
#include "led_load.h"

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
  IOCAF5 = 0;
  if (TMR2IF == 1) {
    start_pi = 1;
    TMR2IF = 0;
  }
}

void configure_interrupt(void) {
  disable_IOC_interrupt();
  enable_IOC_interrupt();
}
