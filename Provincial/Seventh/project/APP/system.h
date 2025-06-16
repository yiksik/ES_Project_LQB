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
#include "adcapp.h"
#include "tim.h"
#include "timapp.h"
#include "keyapp.h"
#include "usart.h"
#include "dma.h"
#include "uartapp.h"
#include "string.h"
#include "iicapp.h"
#include "i2c_hal.h"

extern uint8_t ucled;
extern uint8_t lcd_view;
extern float adc_value;
extern uint8_t height_value;
extern uint8_t th_arr[3];
extern uint8_t level_value;
extern uint8_t set_obj;
extern uint8_t uart_rx_buffer[100];
extern uint8_t uart_buffer_size;
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern uint8_t led2_state;
extern uint8_t led3_state;
extern uint16_t led2_count;
extern uint16_t led3_count;

#endif
