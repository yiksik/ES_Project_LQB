#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "main.h"
#include "stm32g431xx.h"

#include "ledapp.h"
#include "lcdapp.h"

#include "lcd.h"
#include "lcdapp.h"
#include "stdio.h"

#include "rtc.h"
#include "rtcapp.h"

#include "scheduler.h"

#include "adc.h"
#include "adcapp.h"

#include "tim.h"
#include "timapp.h"

#include "usart.h"
#include "dma.h"
#include "string.h"

#include "keyapp.h"

#include "i2c_hal.h"
#include "iicapp.h"

extern char lcd_buffer[30];
extern uint8_t ucled;
extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;
extern uint8_t lcd_view;
extern float adc_value;
extern uint8_t led1_count;
extern float k_value;
extern uint8_t led1_state;
extern uint8_t uart_rx_buffer[20];
extern uint8_t led1_switch;
extern uint8_t time_set[3];
#endif
