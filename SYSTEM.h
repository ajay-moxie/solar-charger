
#include <htc.h>
#include <stdint.h>

//function declaration
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
