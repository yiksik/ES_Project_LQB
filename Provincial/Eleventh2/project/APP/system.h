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
#include "tim.h"
#include "timapp.h"
#include "keyapp.h"
#include "math.h"

extern uint8_t ucled;
extern float duty_pa6, duty_pa7;
extern uint8_t duty_pa6_set, duty_pa7_set;
extern uint8_t lcd_view;
extern float adc_value;
extern uint8_t work_mode;
extern float pa6_duty, pa7_duty;

#endif