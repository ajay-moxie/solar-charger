#ifndef __COMMON_H__
#define __COMMON_H__
#include "SYSTEM.h"
#define NULL (void *)0
typedef enum {
	OFF,
	ON,
}state_t;

typedef enum{
	true,
	false,
}bool_t;

typedef enum{
	SLEEP_READY,
	NO_SLEEP,
}sleep_t;

typedef enum{
	NEGATIVE,
	POSITIVE,
}sense_t;

typedef void(*fn)(void);

#endif


