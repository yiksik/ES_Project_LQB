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
#include "adc.h"
#include "adcapp.h"
#include "timapp.h"
#include "tim.h"
#include "math.h"

extern uint8_t ucled;
extern uint32_t freq_pa1;
extern float adc_value;
extern uint8_t r_value;
extern uint8_t lcd_view;
extern uint8_t led_flag;
extern float duty_pa7;
extern uint32_t freq_pa7;


#endif
