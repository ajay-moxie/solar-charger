#ifndef __LOAD_MGMT_H__
#define __LOAD_MGMT_H__

//LED constants

typedef enum {
  OVP_REACHED = 6,
  OVP_NOT_REACHED = 7
} ovp_mon_t;

typedef enum{
	OVP_VOLTAGE,
	LOAD_SHORT,
	LOW_BATTERY,
	NO_ERROR
}load_error_t;
void load_mgmt();

#endif
