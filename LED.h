
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
void config_LED_port(void);
void disable_green_LED(void);
void disable_red_LED(void);
void display_ovp_fault(void);
void enable_red_LED(void);
void enable_green_LED(void);
void display_bat_low(void);
void blink_red_led(void);
void blink_green_led(void);
void display_open_ckt_fault(void);
void display_short_ckt_fault(void);
void display_CC_stage(void);
void display_CV_stage(void);
