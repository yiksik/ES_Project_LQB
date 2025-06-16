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
#include "uartapp.h"
#include "usart.h"
#include "dma.h"
#include "tim.h"
#include "timapp.h"
#include "iicapp.h"
#include "i2c_hal.h"
#include "math.h"

extern uint8_t ucled;
extern uint8_t size_rx;
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern uint8_t uart_rx_buffer[100];
extern uint8_t lcd_view;
extern uint8_t x_shop, y_shop;
extern float x_value, y_value;
extern uint32_t x_store, y_store;
extern uint8_t led2_state;
extern uint8_t led2_count;

#endif
