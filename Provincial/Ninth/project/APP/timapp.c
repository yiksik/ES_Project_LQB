#include "timapp.h"

uint16_t led1_count = 0;

void tims_init(void)
{
	HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
//	HAL_TIM_Base_Stop_IT(&htim6);
	__HAL_TIM_CLEAR_IT(&htim6, TIM_IT_UPDATE);
	__HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE);
	__HAL_TIM_CLEAR_IT(&htim4, TIM_IT_UPDATE);
	__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
}

void pa6_switch(void)
{
	static uint8_t state = 0;
	state ^= 1;
	if(state)
		HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
	else
		HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		HAL_TIM_Base_Stop_IT(&htim6);		// 关闭中断
		key2down = 0;
		// 长按B2效果
		if(state == 2)
		{
			times[store_pos] = times[0];
			write_eeprom();
			state = 0;
			up_tick = uwTick;
		}
	}
	if(htim->Instance == TIM7)
	{
		if(state == 1 || state == 3)
		{
			HAL_TIM_Base_Stop_IT(&htim7);
			key4down = 0;
			state = 0;		// 回到standby
			pa6_switch();
			ucled &= 0xfe;
			led_renew();
		}
	}
	if(htim->Instance == TIM4)
	{
		if(state == 1)
		{
			run_time--;
			if(run_time == 0)
			{
				state = 0;
				HAL_TIM_Base_Stop_IT(&htim3);
				ucled &= 0xfe;
				led_renew();
				pa6_switch();
				HAL_TIM_Base_Stop_IT(&htim4);
				__HAL_TIM_SetCounter(&htim4, 0);
			}
		}
	}
	if(htim->Instance == TIM3)
	{
		if(state == 1)
		{
			if(++led1_count == 500)
			{
				led1_count = 0;
				ucled ^= 0x01;
				led_renew();
			}
		}
	}
}