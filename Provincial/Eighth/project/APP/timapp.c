#include "timapp.h"

uint16_t tick = 0;
uint8_t run_state = 0;		// 0-关门；1-开门；2-上行；3-下行；4-等待
uint16_t run_count = 0;
uint8_t goal_index = 0;
uint8_t led_pos = 0;
uint8_t count_led = 0;

void tims_init(void)
{
	HAL_TIM_Base_Start_IT(&htim6);
	
}

void pa6_renew(void)
{
	if(work_state == 1 && run_state == 2)
	{
		// 上行
		__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 800);
		HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
	}
	else if(work_state == 1 && run_state == 3)
	{
		// 下行
		__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 600);
		HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
	}
	else
	{
		HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
	}
}

void pa7_renew(void)
{
	if(work_state == 1 && run_state == 0)
	{
		// 关门
		__HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, 500);
		HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
	}
	else if(work_state == 1 && run_state == 1)
	{
		// 开门
		__HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, 600);
		HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
	}
	else
	{
		HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		if(work_state == 0 && tick)
		{
			if(++tick == 1000)
			{
				for(int i = 1; i < 4; ++i)
				{
					if(platform_goal_up[i] == 1)
					{
						platform_goals[goals_num++] = i+1;
					}
				}
				for(int i = 2; i >= 0; --i)
				{
					if(platform_goal_down[i] == 1)
					{
						platform_goals[goals_num++] = i+1;
					}
				}
				goal_index = 0;		// 复位任务索引
				run_state = 0;		// 准备关门
				printf("%02d:%02d:%02d: cur: %d\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds, platform_cur);
				printf("%02d:%02d:%02d: goals_num: %d\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds, goals_num);
				printf("%02d:%02d:%02d: {%d,%d,%d}\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds, platform_goals[0], platform_goals[1], platform_goals[2]);
				work_state = 1;		// 开始工作
				pa7_renew();
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
				printf("%02d:%02d:%02d: Close!\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
			}
		}
		else if(work_state == 1)
		{
			if(run_state == 2)
			{
				if(++count_led == 200)
				{
					count_led = 0;
					led_pos = (led_pos + 1) % 4;
					ucled &= 0x0f;
					ucled |= (0x10 << led_pos);
					led_renew();
				}
			}
			if(run_state == 3)
			{
				if(++count_led == 200)
				{
					count_led = 0;
					if(led_pos == 0)
						led_pos = 3;
					else
						led_pos--;
					ucled &= 0x0f;
					ucled |= (0x10 << led_pos);
					led_renew();
				}
			}
			if(run_state == 0)
			{
				// 关门
				if(++run_count == 4000)
				{
					// 4s
					run_count = 0;
					if(platform_goals[goal_index] > platform_cur)
					{
						// 切换到上行
						run_state = 2;
						pa6_renew();
						pa7_renew();
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
						led_pos = 0;
						ucled |= (0x10 << led_pos);
						led_renew();
						printf("%02d:%02d:%02d: Up!\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
					}
					else
					{
						// 切换到下行
						run_state = 3;
						pa6_renew();
						pa7_renew();
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
						led_pos = 3;
						ucled |= (0x10 << led_pos);
						led_renew();
						printf("%02d:%02d:%02d: Down!\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
					}
				}
			}
			else if(run_state == 2)
			{
				// 上行
				if(++run_count == 6000)
				{
					// 6s
					run_count = 0;
					platform_cur++;		// 平台+1
					printf("%02d:%02d:%02d: cur: %d\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds, platform_cur);
					if(platform_cur == platform_goals[goal_index])
					{
						// 上升到目标楼层，切换到开门, 否则继续上行
						ucled &= ~(0x01 << (platform_cur-1));
						ucled &= 0x0f;
						led_renew();
						run_state = 1;
						pa7_renew();
						pa6_renew();
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
						printf("%02d:%02d:%02d: Open!\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
						goal_index++;
					}
					else
					{
						printf("%02d:%02d:%02d: Up!\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
					}
				}
			}
			else if(run_state == 3)
			{
				// 下行
				if(++run_count == 6000)
				{
					// 6s
					run_count = 0;
					platform_cur--;		// 平台+1
					printf("%02d:%02d:%02d: cur: %d\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds, platform_cur);
					if(platform_cur == platform_goals[goal_index])
					{
						// 下降到目标楼层，切换到开门, 否则继续下行
						ucled &= ~(0x01 << (platform_cur-1));
						ucled &= 0x0f;
						led_renew();
						run_state = 1;
						pa7_renew();
						pa6_renew();
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
						printf("%02d:%02d:%02d: Open!\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
						goal_index++;
					}
					else
					{
						printf("%02d:%02d:%02d: Down!\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
					}
				}
			}
			else if(run_state == 1)
			{
				// 开门
				if(++run_count == 4000)
				{
					// 4s
					run_count = 0;
					if(goal_index == goals_num)
					{
						// 任务完成, 复位
						work_state = 0;
						pa7_renew();
						printf("%02d:%02d:%02d: Over!\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
						for(int i = 0; i < 4; ++i)
						{
							platform_goal_up[i] = platform_goal_down[i] = 0;
							tick = 0;
							goals_num = 0;
						}
					}
					else
					{
						// 还有任务, 切换到等待2s
						run_state = 4;
						pa7_renew();
						printf("%02d:%02d:%02d: Wait!\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
					}
				}
			}
			else if(run_state == 4)
			{
				// 等待2s
				if(++run_count == 2000)
				{
					run_count = 0;
					run_state = 0;		// 切换到关门
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
					pa7_renew();
					printf("%02d:%02d:%02d: Close!\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
				}
			}
		}
	}
}