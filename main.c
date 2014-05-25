
#include "temp.h"
#include "led_load.h"
#include "interrupt.h"
//Setting configuration word1
__CONFIG(FOSC_INTOSC & BOREN_OFF & WDTE_OFF & CP_OFF & CLKOUTEN_OFF & PWRTE_OFF & MCLRE_ON);
//Setting configuration word2
__CONFIG(STVREN_ON & LVP_OFF);

uint16_t count_10sec;
uint8_t start_150ms;

int main(void) {

  charging_stage_t temp;

  sel_sys_clk_int_osc();
  configure_interrupt();
  config_int_switch1();
  configure_adc();
  configure_timer();
  configure_pwm();
  configure_load_switch();
  config_LED_port();
  configure_charger();
  init_vars();
  PEIE = 1;
  enable_tmr2_int();
  count_10sec = 0;
  start_150ms = 0;
  delay_loop_nms(5);

  while(1) {
    if (start_pi == 1) {
      start_pi = 0;
      switch_val = check_switch_position();
      battery_check = check_battery_voltage();
      //counter to dealy detection of PV 3 sec approx
      /*
      pv_det_count = pv_det_count + 1;
      if (pv_det_count == 1500) {
	pv_det_count = 0;
        charger_check = check_charger_present();
	temp = battery_charge_monitor();
	if ((batt_charge < 12) && (bat_vol < BATT_CV_SWITCH_VOL) && (start_charging == 1)) {
          charger_check = No;
        }
      }*/
      //for PV detection
      count_10sec = count_10sec + 1;
      if (count_10sec == 25000) {
	count_10sec = 0;
	start_150ms = 1;
	LATC1 = 0;
	disable_charging();
      }
      else if ((count_10sec == 340) && (start_150ms == 1)) {
	count_10sec = 0;
	start_150ms = 0;
	LATC1 = 0;
	disable_charging();
        charger_check = check_charger_present();
      }
      else if (start_150ms == 1) {
	LATC1 = 0;
	disable_charging();
      }


      if (SW_OFF_PV_Y) {
        load_disconnect();
        batt_charger_fun();
      }
      else if (SW_ON_PV_N) {
	LATC1 = 0;
        disable_charging();
        start_charging = 0;
        disp_low_batt_n_enter_sleep();
        load_connect();
      }
      else if ((SW_ON_PV_Y) && !start_150ms) {
        load_disconnect();
        batt_charger_fun();
      }
      //else {
      //  prepare_sleep();
      //  enter_sleep_mode();
      //}
    }
  }

  return 0;
}
