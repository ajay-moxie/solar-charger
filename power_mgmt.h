#ifndef __POWER_MGMT_H__
#define __POWER_MGMT_H__
#include "common.h"
#define MAX_SLEEP_FN 20
void register_prepare_sleep(fn func);
void register_post_sleep(fn func);
void power_save();
void sleep_init();
#endif
