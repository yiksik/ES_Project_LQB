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
#include "usart.h"
#include "dma.h"
#include "uartapp.h"
#include "string.h"
#include "tim.h"
#include "timapp.h"

extern uint8_t ucled;

extern uint8_t uart_rx_buffer[100];
extern uint8_t uart_buffer_size;
extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;

typedef struct{
	uint8_t state;	// 0-空闲；1-CNBR; 2-VNBR
	char title[4];	// 车牌
	uint32_t hours; // 进入小时
	uint32_t secs;	// 进入秒
} pos_t;

extern pos_t car_pos[8];
extern float cnbr_fee, vnbr_fee;
extern uint8_t lcd_view;
extern uint8_t idle_num, cnbr_num, vnbr_num;

#endif
