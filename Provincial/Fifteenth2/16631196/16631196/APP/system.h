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

extern uint8_t ucled;
extern float adc_value;
extern uint8_t lcd_view;
extern float pu_value, pd_value;
extern uint8_t mode, lock;
extern uint8_t set_obj;
extern float para_show[2];
extern uint8_t error;
extern uint8_t duty_pa1, duty_pa2;
extern uint32_t add_all, add_set1, add_reset1, add_set2, add_reset2;

#endif
