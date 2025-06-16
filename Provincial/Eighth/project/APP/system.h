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
#include "rtc.h"
#include "rtcapp.h"
#include "tim.h"
#include "timapp.h"

extern uint8_t ucled;
extern RTC_TimeTypeDef sTime;

extern uint8_t platform_cur;
extern uint8_t platform_goal_up[4];
extern uint8_t platform_goal_down[4];
extern uint8_t work_state;

extern uint16_t tick;

extern uint8_t platform_goals[3];
extern uint8_t goals_num;

extern uint8_t run_state;		// 0-关门；1-开门；2-上行；3-下行；4-等待

#endif
