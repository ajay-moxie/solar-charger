
#include <htc.h>
#include <stdint.h>

#define ADC_CHANNEL_0 0
#define ADC_CHANNEL_1 1
#define ADC_CHANNEL_2 2
#define ADC_CHANNEL_3 3
#define ADC_CHANNEL_4 4
#define ADC_CHANNEL_5 5
#define ADC_CHANNEL_6 6
#define ADC_CHANNEL_7 7
#define ADC_CHANNEL_8 8
#define ADC_CHANNEL_9 9
#define ADC_CHANNEL_10 10
#define ADC_CHANNEL_11 11

void config_adc(void);
static void sampling_time_delay(void);
void disable_adc(void);
void enable_adc(void);
void select_adc_channel(uint8_t channel);
void do_adc_conversion(void);
uint16_t load_adc_result(void);
void config_adc_pin(uint8_t pin);
