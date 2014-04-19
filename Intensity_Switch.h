
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
