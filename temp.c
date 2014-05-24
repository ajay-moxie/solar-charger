#include "temp.h"
//main functions
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


void start_pwm1(void) {
  TMR2 = PWM_PERIOD;
  //Loading PR2 for 40KHz PWM
  PR2 = PWM_PERIOD;
  enable_load_switch();
  enable_pwm1();
}

void enable_tmr2_int(void) {
  clear_int_tmr2();
  enable_tmr2();
  TMR2IE = 1;
}

void start_pwm4(void) {
  TMR2 = CHARGER_PWM_PERIOD;
  //Loading PR2 for 16KHz PWM
  PR2 = CHARGER_PWM_PERIOD;
  //clear_int_tmr2();
  //enable_tmr2();
  //wait_for_int_tmr2();
}

void pi_controller(void) {
  ovp_mon_t ovp_cond;
  load_regulation_t load_cond;

  ovp_cond = monitor_overload_voltage();
  if (ovp_cond == OVP_REACHED) {
    disable_load_switch();
    disable_pwm1();
    display_ovp_fault();
  }
  else {
    load_cond = monitor_load_regulation();
    /*
    if (load_cond == OPEN_CKT_LOAD) {
      disable_load_switch();
      disable_pwm1();
      display_open_ckt_fault();
    }
    else*/ if (load_cond == SHORT_CKT_LOAD) {
      disable_load_switch();
      disable_pwm1();
      display_short_ckt_fault();
    }
    else {
      enable_load_switch();
      enable_pwm1();
      feedback = feedback + load_vol;
      feedback = feedback >> 1;
      calculate_duty_cycle();
      update_pwm1_duty_cycle(duty_cycle);
    }
  }
}

void pi_controller_pv(void) {
  charging_stage_t charging_cond;

  charging_cond = battery_charge_monitor();
  //PWM4POL = 0;
  //update_pwm4_duty_cycle(180);
  //enable_charging();
      //LATC1 = 1;
      //disable_charging();
  //flag is used as after 6 sec time battery voltage will go low and controller should not detect it as CC mode
  if ((bat_vol <= BATT_CV_SWITCH_VOL) && (start_CV_stage == 0)) { 
    if (charging_cond == CHARGER_PWM_CTL_REQ) {
      enable_charging();
      charger_feedback = batt_charge + charger_feedback;
      charger_feedback = charger_feedback >> 1;
      calc_charger_duty_cycle();
      update_pwm4_duty_cycle(charger_duty_cycle);
      display_CC_stage();
    }
    else {
      LATC1 = 1;
      disable_charging();
      display_CC_stage();
    }
  }
  else {
    if (start_CV_stage == 0) {
      start_CV_stage = 1;
      disable_charging();
      init_CV_var();
      update_pwm4_duty_cycle(40);
      delay_loop_ns(6);
      enable_charging();
    }
    charger_feedback = bat_vol + charger_feedback;
    charger_feedback = charger_feedback >> 1;
    calc_charger_duty_cycle();
    update_pwm4_duty_cycle(charger_duty_cycle);
    //update_pwm4_duty_cycle(260);
    display_CV_stage();
    // to be confirmed by delay of 10s - if current remains then only disable charging
    if (batt_charge >= STOP_CHARGING_VOL) {     
      stop_charging_count = stop_charging_count + 1;
      if (stop_charging_count == 32000) {
	stop_charging_count = 0;
        start_charging = 0;
      }
    }
  }
}

void initiate_charging(void) {
  if (start_charging == 0) {
    start_pwm4();
    enable_charging();
    start_charging = 1;
  }
  pi_controller_pv();
}

void init_vars(void) {
  first_run = 1;
  switch_val = OFF;
  battery_check = Low;
  charger_check = No;
  start_CV_stage = 0;
  start_charging = 0;
  pv_det_count = 0;
  stop_charging_count = 0;
}

void prepare_sleep(void) {
  disable_pwm1();
  disable_load_switch();
  disable_charging();
  start_charging = 0;
}

void batt_charger_fun(void) {
  if (battery_check == Low || battery_check == Mid) {
    initiate_charging();
  }
  else if (start_charging == 1) {
    pi_controller_pv();
  }
  else {
    charging_stop();	
  }
}

void load_connect(void) {
  init_pwm4_var();
  if (first_run == 1) {
    first_run = 0;
    start_pwm1();
  }
  pi_controller();
}

void load_disconnect(void) {
  first_run = 1;
  disable_pwm1();
  disable_load_switch();
  init_pwm1_var();
}

void disp_low_batt_n_enter_sleep(void) {
  if (battery_check == Low) {
    display_bat_low();
    prepare_sleep();
    enter_sleep_mode();
  }
}
