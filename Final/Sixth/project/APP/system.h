#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "main.h"
#include "stm32g431xx.h"

#include "lcd.h"
#include "lcdapp.h"
#include "stdio.h"
#include "stdarg.h"
#include "ledapp.h"
#include "scheduler.h"
#include "adc.h"
#include "dma.h"
#include "adcapp.h"
#include "keyapp.h"
#include "timapp.h"
#include "tim.h"
#include "i2c_hal.h"
#include "iicapp.h"

extern uint8_t ucled;
extern float adc_value;
extern uint8_t lcd_view; 
extern uint8_t duty1, duty2;
extern uint8_t state_output;
extern uint32_t freq;

#endif

