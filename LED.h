
#include <htc.h>
#include <stdint.h>

#define OVP_FAULT_DELAY 200
#define OPEN_CKT_FAULT_DELAY 400
#define SHORT_CKT_FAULT_DELAY 400
#define CC_STAGE_DELAY 1000
#define CV_STAGE_DELAY 400
#define RED_LED_BLINK_DELAY 800
#define GREEN_LED_BLINK_DELAY 800

uint8_t display_flag;
uint16_t led_cnt;

//function declaration
void delay_loop_nms(uint16_t ms_time);

