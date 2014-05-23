
#include "ADC.h"

void config_adc(void) {
  //Select external pin for Vref
  //ADPREF0 = 0;
  //ADPREF1 = 1;
  //Select Fosc/16 as clock
  //ADCS0 = 1;
  //ADCS1 = 0;
  //ADCS2 = 1;
  //ADCS = 0x5;
  //Right justify result
  //ADFM = 1;
  ADCON1 = 0xD0;
  //Turn on ADC
  ADON = 1;
}

static void sampling_time_delay(void) {
  uint8_t i;

  for (i=0; i<20; i++) {
    NOP();
  }
}

void disable_adc(void) {
  ADON = 0;
}

void enable_adc(void) {
  ADON = 1;
}

void select_adc_channel(uint8_t channel) {
  uint8_t int_channel;

  int_channel = 0;
  int_channel = channel << 2;
  //Select channel to convert
  ADCON0 = int_channel | 0x01;
}

void do_adc_conversion(void) {
  //Wait for sampling time
  sampling_time_delay();
  //Start conversion
  ADGO = 1;
  //Wait for convertion to complete
  while(ADGO == 1);  
}

uint16_t load_adc_result(void) {
  uint16_t adc_result;

  adc_result = 0;
  adc_result = ADRESH & 0x3; 
  adc_result = adc_result << 8;
  adc_result = adc_result | ADRESL;
  adc_result = adc_result & 0x3FF;

  return adc_result;
}

void config_adc_pin(uint8_t pin) {

  switch(pin) {
    case ADC_CHANNEL_0 : ANSA0 = 1;
                         LATA0 = 0;
                         TRISA0 = 1;
		         break;
    case ADC_CHANNEL_1 : ANSA1 = 1;
                         LATA1 = 0;
                         TRISA1 = 1;
		         break;
    case ADC_CHANNEL_2 : ANSA2 = 1;
                         LATA2 = 0;
                         TRISA2 = 1;
		         break;
    case ADC_CHANNEL_3 : ANSA4 = 1;
                         LATA4 = 0;
                         TRISA4 = 1;
		         break;
    case ADC_CHANNEL_4 : ANSC0 = 1;
                         LATC0 = 0;
                         TRISC0 = 1;
		         break;
    case ADC_CHANNEL_5 : ANSC1 = 1;
                         LATC1 = 0;
                         TRISC1 = 1;
		         break;
    case ADC_CHANNEL_6 : ANSC2 = 1;
                         LATC2 = 0;
                         TRISC2 = 1;
		         break;
    case ADC_CHANNEL_7 : ANSC3 = 1;
                         LATC3 = 0;
                         TRISC3 = 1;
		         break;
    case ADC_CHANNEL_8 : ANSC6 = 1;
                         LATC6 = 0;
                         TRISC6 = 1;
		         break;
    case ADC_CHANNEL_9 : ANSC7 = 1;
                         LATC7 = 0;
                         TRISC7 = 1;
		         break;
    case ADC_CHANNEL_10 : ANSB4 = 1;
                          LATB4 = 0;
                          TRISB4 = 1;
		          break;
    case ADC_CHANNEL_11 : ANSB5 = 1;
                          LATB5 = 0;
                          TRISB5 = 1;
		          break;
  }
}
