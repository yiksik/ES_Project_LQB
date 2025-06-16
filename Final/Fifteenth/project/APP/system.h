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
#include "usart.h"
#include "dma.h"
#include "string.h"
#include "tim.h"
#include "timapp.h"
#include "adc.h"
#include "adcapp.h"
#include "uartapp.h"
#include "keyapp.h"
#include "math.h"

extern uint8_t ucled;
extern uint8_t uart_rx_buffer[500];
extern uint32_t pa15_freq;
extern float adc_value;
extern uint8_t adc_level;
extern float v_value;
extern float v_value_real;
extern float r_value;
extern uint8_t b_value;
extern uint8_t device_state;
extern uint8_t scene_current;
extern uint16_t uart_buffer_size;
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;

typedef struct{
	float x;
	float y;
} point_t;

extern point_t points_buffer[100];
extern int point_start;
extern int point_end;
extern uint8_t lcd_view;
extern float ts_value;
extern uint32_t tt_value;
extern uint8_t led_count;
#endif


