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
#include "adcapp.h"
#include "adc.h"
#include "tim.h"
#include "timapp.h"
#include "math.h"

extern uint8_t ucled;
extern float adc_value;
extern uint32_t freq_pa7;
extern float duty_value;
extern uint8_t r_value, k_value, r_value_show, k_value_show;
extern float v_value;
extern uint8_t lcd_view;
extern uint8_t mode;
extern uint8_t n_value;
extern float mh_value, ml_value;
extern uint8_t tf_state;
extern uint8_t set_obj;
extern uint8_t duty_lock;
extern uint8_t count_led2;

#endif
