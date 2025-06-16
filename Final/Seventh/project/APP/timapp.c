#include "timapp.h"

uint32_t tim3_ic_buffer[30] = {0};
uint32_t freq_ic = 0;
uint32_t freq_out = 1000;
uint8_t wet_value = 0;
uint16_t count_t6 = 0;
rec_t record_arr[60];
uint8_t led1_state = 0;
uint8_t led2_state = 0;
uint8_t count = 0;


void tims_init(void)
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	
	HAL_TIM_IC_Start_DMA(&htim3, TIM_CHANNEL_2, tim3_ic_buffer, 30);
	
	HAL_TIM_Base_Start_IT(&htim6);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		if(++count_t6 >= record_gap * 1000)
		{
//			adc_proc();
//			tim3_ic_proc();
			rtc_proc();
			record_arr[record_index].temper = temper_value;
			record_arr[record_index].wet = wet_value;
			record_arr[record_index].hour = sTime.Hours;
			record_arr[record_index].min = sTime.Minutes;
			record_arr[record_index].sec  = sTime.Seconds;
			record_index = (record_index + 1) % 60;
			record_times++;
			ucled ^= 0x04;
			led_renew();
			count_t6 = 0;
		}
		if(++count == 200)
		{
			count = 0;
			if(led1_state)
			{
				ucled ^= 0x01;
			}
			if(led2_state)
			{
				ucled ^= 0x02;
			}
			if(led1_state || led2_state)
			{
				led_renew();
			}
		}
	}
}

void tim3_ic_proc(void)
{
	uint32_t temp = 0;
	for(int i = 0; i < 30; i += 3)
	{
		temp += tim3_ic_buffer[i];
	}
	// 1 000 000 / (temp/10)
	freq_ic = 10000000 / temp;
	if(freq_ic < 1000)
		freq_ic = 1000;
	else if(freq_ic > 10000)
		freq_ic = 10000;
	wet_value = 80 * (freq_ic - 1000) / 9000 + 10;
	
	if(wet_value > th_wet && led2_state == 0)
	{
		ucled |= 0x02;
		led_renew();
		led2_state = 1;
	}
	else if(wet_value < th_wet && led2_state == 1)
	{
		ucled &= 0xfd;
		led_renew();
		led2_state = 0;
	}
}

void pwm_freq_renew(void)
{
	// 80000000 / 100 / freq_out - 1
	__HAL_TIM_SET_PRESCALER(&htim2, 800000 / freq_out - 1);
}