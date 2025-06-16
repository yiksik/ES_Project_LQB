#ifndef __RTCAPP_H
#define __RTCAPP_H

#include "system.h"

void rtc_proc(void);
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc);

#endif
