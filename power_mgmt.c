#include "power_mgmt.h"
static fn prepare_sleep[MAX_SLEEP_FN];
static fn post_sleep[MAX_SLEEP_FN];

void register_prepare_sleep(fn func)
{
	int i = 0;
	while((prepare_sleep[i] != NULL) && (i < MAX_SLEEP_FN))
		i++;
	prepare_sleep[i] = func;
}

void register_post_sleep(fn func)
{
	int i = 0;
	while((post_sleep[i] != NULL) && (i < MAX_SLEEP_FN))
		i++;
	post_sleep[i] = func;
}

void power_save()
{
	int i;
	i = 0;
	while((prepare_sleep[i] != NULL) && (i < MAX_SLEEP_FN)){
		prepare_sleep[i]();
		i++;
	}
		
	select_internal_lp_osc();
	enter_sleep_mode();
	select_internal_hp_osc();

	i = 0;
	while((post_sleep[i] != NULL) && (i < MAX_SLEEP_FN)){
		post_sleep[i]();
		i++;
	}
}

void sleep_init()
{
	int i;
	for(i = 0; i < MAX_SLEEP_FN; i++){
		prepare_sleep[i] = NULL;
		post_sleep[i] = NULL;
	}
}
