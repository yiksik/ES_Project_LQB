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
#include "adcapp.h"
#include "adc.h"
#include "keyapp.h"

extern uint8_t ucled;
extern uint8_t lcd_view;
extern float adc_value;
extern uint32_t time_rec;
extern uint32_t time_start;
extern uint8_t state;
extern float th_temper[2];
extern float th_temper_real[2];

#endif
