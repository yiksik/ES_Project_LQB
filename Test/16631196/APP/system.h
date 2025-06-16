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
#include "tim.h"
#include "timapp.h"

extern uint32_t freq_pa5_ch1, freq_pa1_ch2, freq_pa2_ch3, freq_pa3_ch4;
extern float duty_pa1, duty_pa2;

#endif
