
#include "ADC.h"


void config_analog_pins(void) {
  ANSA0 = 1;
  LATA0 = 0;
  TRISA0 = 1;
  ANSA1 = 1;
  LATA1 = 0;
  TRISA1 = 1;
  ANSA4 = 1;
  LATA4 = 0;
  TRISA4 = 1;
  ANSB4 = 1;
  LATB4 = 0;
  TRISB4 = 1;
  ANSB5 = 1;
  LATB5 = 0;
  TRISB5 = 1;
  ANSC0 = 1;
  LATC0 = 0;
  TRISC0 = 1;
  ANSC2 = 1;
  LATC2 = 0;
  TRISC2 = 1;
  ANSC6 = 1;
  LATC6 = 0;
  TRISC6 = 1;
  ANSC7 = 1;
  LATC7 = 0;
  TRISC7 = 1;
}

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

void sampling_time_delay(void) {
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

battery_voltage_t check_battery_voltage(void) {
  uint8_t loop0;
  battery_voltage_t return_val;
  uint16_t adc_int_val;

  bat_vol = 0;
  return_val = Low;
  adc_int_val = 0;

  select_adc_channel(BATTERY_VOL_MON);
  for (loop0=0; loop0<4; loop0++) {
    do_adc_conversion();
    adc_int_val = load_adc_result();
    bat_vol = bat_vol + adc_int_val;
  }
  bat_vol = bat_vol >> 2;
  bat_vol = bat_vol & 0x3FF;

  if (bat_vol <= BAT_LO_VOL) {
    return_val = Low;
  }
  else if (bat_vol >= BAT_HI_VOL) {
    return_val = High;
  }
  else {
    return_val = Mid;
  }

  return return_val;
}

charger_present_t check_charger_present(void) {
  uint8_t loop1;
  charger_present_t return_val;
  uint16_t adc_int_val;

  charger_vol = 0;
  return_val = No;
  adc_int_val = 0;

  select_adc_channel(CHARGER_SENSE);
  for (loop1=0; loop1<4; loop1++) {
    do_adc_conversion();
    adc_int_val = load_adc_result();
    charger_vol = charger_vol + adc_int_val;
  }
  charger_vol = charger_vol >> 2;
  charger_vol = charger_vol & 0x3FF;

  if (charger_vol < CHARGER_DET) {
    return_val = Yes;
  }

  return return_val;
}

ovp_mon_t monitor_overload_voltage(void) {
  uint8_t loop2;
  ovp_mon_t return_val;
  uint16_t adc_int_val;

  ovp_vol = 0;
  adc_int_val = 0;
  return_val = OVP_REACHED;

  select_adc_channel(OVERLOAD_SENSE);
  for (loop2=0; loop2<4; loop2++) {
    do_adc_conversion();
    adc_int_val = load_adc_result();
    ovp_vol = ovp_vol + adc_int_val;
  }
  ovp_vol = ovp_vol >> 2;
  ovp_vol = ovp_vol & 0x3FF;

  if (ovp_vol >= OVP_VOL) {
    return_val = OVP_REACHED;
  }
  else {
    return_val = OVP_NOT_REACHED;
  }

  return return_val;
}

load_regulation_t monitor_load_regulation(void) {
  uint8_t loop3;
  load_regulation_t return_val;
  uint16_t adc_int_val;

  load_vol = 0;
  return_val = OPEN_CKT_LOAD;
  adc_int_val = 0;

  select_adc_channel(LOAD_VOLTAGE);
  for (loop3=0; loop3<4; loop3++) {
    do_adc_conversion();
    adc_int_val = load_adc_result();
    load_vol = load_vol + adc_int_val;
  }
  load_vol = load_vol >> 2;
  load_vol = load_vol & 0x3FF;

  if (load_vol <= LOAD_OPEN_CKT_VOL) {
    return_val = OPEN_CKT_LOAD;
  }
  else if (load_vol >= LOAD_SHORT_CKT_VOL) {
    return_val = SHORT_CKT_LOAD;
  }
  else {
    return_val = LOAD_REG_100;
  }

  return return_val;
}

charging_stage_t battery_charge_monitor(void) {
  uint8_t loop4;
  charging_stage_t return_val;
  uint16_t adc_int_val;

  batt_charge = 0;
  adc_int_val = 0;
  return_val = CHARGER_PWM_CTL_NOT_REQ;

  select_adc_channel(BATTERY_CHARGE_VOL);
  for (loop4=0; loop4<4; loop4++) {
    do_adc_conversion();
    adc_int_val = load_adc_result();
    batt_charge = batt_charge + adc_int_val;
  }
  batt_charge = batt_charge >> 2;
  batt_charge = batt_charge & 0x3FF;

  if (batt_charge < BATT_CC_VOL) {
    return_val = CHARGER_PWM_CTL_NOT_REQ;
  }
  else {
    return_val = CHARGER_PWM_CTL_REQ;
  }

  return return_val;
}

thermistor_vol_t temperature_monitor(void) {
  uint8_t loop7;
  uint16_t adc_int_val;

  thermistor_voltage = 0;
  adc_int_val = 0;

  select_adc_channel(TEMP_COMP);
  for (loop7=0; loop7<4; loop7++) {
    do_adc_conversion();
    adc_int_val = load_adc_result();
    thermistor_voltage = thermistor_voltage + adc_int_val;
  }
  thermistor_voltage = thermistor_voltage >> 2;
  thermistor_voltage = thermistor_voltage & 0x3FF;

  return THERMISTOR_VOL;
}

void init_adc_var(void) {
  bat_vol = 0;
  ovp_vol = 0;
  charger_vol = 0;
  load_vol = 0;
  batt_charge = 0;
  thermistor_voltage = 0;
  hysterisis_flag = 0;
  count = 0;
}

void configure_adc(void) {
  init_adc_var();
  config_analog_pins();
  config_adc();
}
