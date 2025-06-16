#ifndef __TIMAPP_H
#define __TIMAPP_H

#include "system.h"

void tims_init(void);
void pwm_freq_renew(void);
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim);

#endif
