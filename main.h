
#include <htc.h>
#include <stdint.h>

#include "SYSTEM.h"
#include "Intensity_Switch.h"
#include "ADC.h"
#include "TIMER.h"
#include "PWM.h"
#include "Load_Switch.h"
#include "LED.h"
#include "Charging.h"

#define SW_OFF_PV_N ((switch_val == OFF) && (charger_check == No))
#define SW_OFF_PV_Y ((switch_val == OFF) && (charger_check == Yes))
#define SW_ON_PV_N ((switch_val == ON) && (charger_check == No))
#define SW_ON_PV_Y ((switch_val == ON) && (charger_check == Yes))

switch_position_t switch_val;
battery_voltage_t battery_check;
charger_present_t charger_check;
uint8_t first_run;
uint16_t pv_det_count;
uint16_t stop_charging_count;

//ADC functions
void config_analog_pins(void);
void config_adc(void);
void sampling_time_delay(void);
void disable_adc(void);
void enable_adc(void);
void select_adc_channel(uint8_t channel);
void do_adc_conversion(void);
battery_voltage_t check_battery_voltage(void);
charger_present_t check_charger_present(void);
//charger_present_t check_charger_present(charger_present_t status);
ovp_mon_t monitor_overload_voltage(void);
//uint16_t load_adc_result(void)
load_regulation_t monitor_load_regulation(void);
charging_stage_t battery_charge_monitor(void);
void init_adc_var(void);
void configure_adc(void);

//Charging functions
void disable_charging(void);
void enable_charging(void);
void init_pwm4_var(void);
void init_CV_var(void);
void config_pwm4(void);
void update_pwm4_duty_cycle(uint16_t duty_cyc_int);
void calc_charger_duty_cycle(void);
void configure_charger(void);
void reset_charger_config(void);
void charging_stop(void);

//Intensity switch functions
void enable_IOC_interrupt(void);
void disable_IOC_interrupt(void);
void config_int_switch1(void);
void detect_switch(void);
switch_position_t check_switch_position(void);
void interrupt update_intensity_flags_int(void);
void configure_interrupt(void);

//LED functions
//void delay_loop_nms(int ms_time);
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

//Load switch functions
void config_load_switch (void);
void enable_load_switch(void);
void disable_load_switch(void);
void configure_load_switch(void);

//PWM functions
void disable_pwm1(void);
void enable_pwm1(void);
void update_pwm1_duty_cycle(uint16_t duty_cycle);
void calculate_duty_cycle(void);
void init_pwm1_var(void);
void configure_pwm(void);

//System functions
void select_internal_lp_osc(void);
void select_internal_hp_osc(void);
void select_internal_osc(void);
void wait_for_hp_osc_ready(void);
void wait_for_lp_osc_ready(void);
void wait_for_hp_osc_stable(void);
void config_digital_pins(void);
void enter_sleep_mode(void);
void sel_sys_clk_int_osc(void);
void fvr_enable(void);
void fvr_disable(void);
void config_fvr(void);

//Timer functions
void config_tmr2(void);
void enable_tmr2(void);
void clear_int_tmr2(void);
void wait_for_int_tmr2(void);
void config_tmr1(void);
void enable_tmr1(void);
void clear_int_tmr1(void);
void wait_for_int_tmr1(void);
//void delay_loop_nms(uint16_t ms_time);
void configure_timer(void);

//main functions

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

void delay_loop_ns(uint16_t t_sec) {
  uint16_t delay_loop;

  for (delay_loop=0; delay_loop<t_sec; delay_loop++) {
    delay_loop_nms(800);
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
