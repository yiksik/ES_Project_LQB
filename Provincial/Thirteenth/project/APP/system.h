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
#include "timapp.h"
#include "tim.h"

extern uint8_t lcd_view;
extern uint8_t ucled;
extern uint8_t b1_down, b2_down, b3_down;
extern uint8_t b1_num, b2_num, b3_num;
extern uint8_t ans[3];
extern uint8_t ans_wrong;
extern uint8_t led2_state;
extern uint32_t led2_count;

#endif
