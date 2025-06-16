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
#include "keyapp.h"
#include "tim.h"
#include "timapp.h"
#include "adc.h"
#include "adcapp.h"
#include "usart.h"
#include "uartapp.h"
#include "rtc.h"
#include "rtcapp.h"
#include "iicapp.h"
#include "i2c_hal.h"
#include "string.h"
#include "dac.h"
#include "dacapp.h"

extern uint8_t ucled;
extern uint8_t uart_rx_buffer[100];
extern uint16_t uart_rx_buffer_size;
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;

#endif
