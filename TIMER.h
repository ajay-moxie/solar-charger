
#include <htc.h>
#include <stdint.h>


#define TMR2_PERIOD 100

void config_tmr2(void);
void enable_tmr2(void);
void disable_tmr2(void);
void clear_int_tmr2(void);
void wait_for_int_tmr2(void);
void config_tmr1(void);
void enable_tmr1(void);
void disable_tmr1(void);
void clear_int_tmr1(void);
void wait_for_int_tmr1(void);
void delay_loop_nms(uint8_t ms_val);
void delay_loop_ns(uint8_t t_sec);
void configure_timer(void);
