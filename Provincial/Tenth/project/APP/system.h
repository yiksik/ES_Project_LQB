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
#include "tim.h"
#include "timapp.h"

extern uint8_t ucled;
extern uint8_t lcd_view;
extern float adc_value;
extern uint8_t set_obj;
extern float temper_th[2];
extern uint8_t led_pos[2];
extern uint8_t status_value;
extern uint8_t led_count;

#endif
