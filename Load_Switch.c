#include "power_mgmt.h"
#include "Load_Switch.h"
#include "common.h"
#include "config.h"

static void load_switch_sleep_exit(void);
static void load_switch_sleep_prepare(void);
/*void config_load_switch (void) {
  ANSC3 = 0;
  TRISC3 = 0;
}*/

void enable_load_switch(void) {
  LATC3 = LOAD_SRT_CKT_PROTECTION_SW_ENABLE;
}

void disable_load_switch(void) {
  LATC3 = !LOAD_SRT_CKT_PROTECTION_SW_ENABLE;
}

void load_switch_init(void) {
  load_switch_sleep_exit();
#ifdef LED_LOAD_POWER_MGMT
  register_prepare_sleep(load_switch_sleep_prepare);
  register_post_sleep(load_switch_sleep_exit);
#endif
} 

static void load_switch_sleep_exit(void) {
  disable_load_switch();
  ANSC3 = 0;
  TRISC3 = 0;
}

static void load_switch_sleep_prepare(void)
{
  disable_load_switch();
  ANSC3 = 1;
  TRISC3 = 1;

}
