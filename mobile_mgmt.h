#ifndef __MOBILE_MGMT_H__
#define __MOBILE_MGMT_H__

void mobile_mgmt();
void mobile_mgmt_init();

state_t mobile_charging_state();
void set_mobile_charging_state(state_t state);
#endif
