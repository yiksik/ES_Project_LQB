#ifndef __TIMAPP_H
#define __TIMAPP_H

#include "system.h"
void tims_init(void);
void ic_proc(void);
void pa1_duty_renew(void);
void pa1_freq_renew(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
