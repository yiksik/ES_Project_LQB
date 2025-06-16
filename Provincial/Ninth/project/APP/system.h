#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "main.h"
#include "stm32g431xx.h"

#include "lcd.h"
#include "lcdapp.h"
#include "stdio.h"
#include "stdarg.h"
#include "scheduler.h"
#include "ledapp.h"
#include "tim.h"
#include "timapp.h"
#include "keyapp.h"
#include "i2c_hal.h"
#include "iicapp.h"

extern uint8_t ucled;
extern uint8_t store_pos;

extern uint8_t key2down;
extern uint32_t down_tick, up_tick;

typedef struct{
	uint8_t hours;
	uint8_t mins;
	uint8_t secs;
} time_t;


extern time_t times[6];
extern uint8_t state;
extern uint8_t key4down;
extern uint32_t run_time;
extern uint16_t led1_count;
extern uint8_t set_obj;

#endif
