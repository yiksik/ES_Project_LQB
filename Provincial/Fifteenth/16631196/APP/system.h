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
#include "keyapp.h"
#include "tim.h"
#include "timapp.h"

extern uint8_t ucled;
extern uint8_t lcd_view;
extern uint8_t lcd0_view;
extern float freq_pa, freq_pb;
extern float period_pa_us, period_pb_us;
extern float pd_value, ph_value, px_value;
extern uint8_t nda_value, ndb_value, nha_value, nhb_value;
extern uint8_t set_obj;
extern uint8_t led8_state;

#endif
