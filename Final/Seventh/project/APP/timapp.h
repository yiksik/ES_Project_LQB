#ifndef __TIMAPP_H
#define __TIMAPP_H

#include "system.h"

void tims_init(void);
void tim3_ic_proc(void);
void pwm_freq_renew(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
