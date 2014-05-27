
#include <htc.h>
#include <stdint.h>


uint8_t start_pi = 0;


//function declaration
void enable_IOC_interrupt(void);
void disable_IOC_interrupt(void);

void interrupt update_intensity_flags_int(void);
void configure_interrupt(void);
void DI();
void EI();
