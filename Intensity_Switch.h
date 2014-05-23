
#include <htc.h>
#include <stdint.h>


typedef enum {
  OFF,
  ON
} switch_position_t;

uint8_t switch1 = 0;
uint8_t start_pi = 0;
uint8_t sw_cnt_low = 0;
uint8_t sw_cnt_high = 0;

//function declaration
void enable_IOC_interrupt(void);
void disable_IOC_interrupt(void);
void config_int_switch1(void);
void detect_switch(void);
switch_position_t check_switch_position(void);
void interrupt update_intensity_flags_int(void);
void configure_interrupt(void);
