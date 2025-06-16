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
#include "tim.h"
#include "timapp.h"
#include "math.h"
#include "i2c_hal.h"
#include "iicapp.h"

extern uint8_t ucled;
extern float adc_pa4, adc_pa5, adc_pa4_real, adc_pa5_real;
extern uint32_t freq_pa1;
extern uint8_t n_value[2];
extern float a_value[2], t_value[2], h_value[2];
extern uint8_t channel;
extern uint8_t lcd_view;
extern uint8_t x_value, y_value;
extern uint8_t output_mode;
extern float freq_pa7;
extern uint8_t led3_state;
extern uint8_t led3_count;

#endif
