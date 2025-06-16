#include "rtcapp.h"

RTC_TimeTypeDef sTime = {0};
RTC_DateTypeDef sDate = {0};

void rtc_proc(void)
{
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}