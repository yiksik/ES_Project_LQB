#include "rtcapp.h"

RTC_TimeTypeDef sTime = {0};
RTC_DateTypeDef sDate = {0};

void rtc_proc(void)
{
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);  // 显示时钟的时候使用%02d
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);  // 不可省略
	
	if(lcd_view == 0)
	{
		// 在LCD显示界面下，更新显示的时间
		sprintf(lcd_buffer, "%02d-%02d-%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
		lcd_disp(Line3, 3, 11);
	}
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
  // 闹钟A中断服务函数: 定时上报电压
	HAL_RTC_GetTime(hrtc, &sTime, RTC_FORMAT_BIN);  // 显示时钟的时候使用%02d
	HAL_RTC_GetDate(hrtc, &sDate, RTC_FORMAT_BIN);  // 不可省略
	printf("%.2f+%.1f+%02d%02d%02d\r\n", adc_value,k_value,  sTime.Hours, sTime.Minutes, sTime.Seconds);
}

void rtc_set_alarm(void)
{
	RTC_AlarmTypeDef sAlarm = {0};
	sAlarm.AlarmTime.Hours = time_set[0];
  sAlarm.AlarmTime.Minutes = time_set[1];
  sAlarm.AlarmTime.Seconds = time_set[2];
  sAlarm.AlarmTime.SubSeconds = 0;
  sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
}