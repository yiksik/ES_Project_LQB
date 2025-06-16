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
#include "adc.h"
#include "dma.h"
#include "adcapp.h"
#include "tim.h"
#include "timapp.h"
#include "keyapp.h"
#include "rtcapp.h"
#include "rtc.h"
#include "usart.h"
#include "string.h"
#include "uartapp.h"
#include "i2c_hal.h"
#include "iicapp.h"

extern uint8_t ucled;
extern float adc_value;
extern uint32_t freq_ic;
extern uint32_t freq_out;
extern int temper_value;
extern uint8_t wet_value;
extern RTC_TimeTypeDef sTime;
extern uint8_t lcd_view;
extern uint32_t record_times;
extern uint8_t record_index;
extern uint8_t set_obj;
extern int th_temper;
extern uint8_t th_wet;
extern uint8_t record_gap;

typedef struct{
	int temper;
	uint8_t wet;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
} rec_t;

extern rec_t record_arr[60];
extern uint8_t uart_buffer[100];
extern uint8_t uart_buffer_size;
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern uint8_t led1_state;
extern uint8_t led2_state;

#endif
