#include "adcapp.h"

uint32_t adc_buffer[30] = {0};
float adc_value = 0.0f;
uint8_t height_value = 0;
uint8_t level_value = 0;
uint8_t last_level = 0;

void adc_init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc2, adc_buffer, 30);
	
	HAL_Delay(5);		// DMA搬运没有那么快，延时一下再读
	// 先读取一次
	adc_value = adc_buffer[0] * 3.3f / 4096.0f;
	height_value = adc_value * 100.0f / 3.3f;
	if(height_value <= th_arr[0])
	 level_value = 0;
	else if(height_value <= th_arr[1])
	 level_value = 1;
	else if(height_value <= th_arr[2])
	 level_value = 2;
	else
		level_value = 3;
	last_level = level_value;
}

void adc_proc(void)
{
	float temp = 0.0f;
	for(int i = 0; i < 30; i += 3)
	{
		temp += adc_buffer[i];
	}
	adc_value = temp * 3.3f / 40960.0f;
	height_value = adc_value * 100.0f / 3.3f;
	if(height_value <= th_arr[0])
	 level_value = 0;
	else if(height_value <= th_arr[1])
	 level_value = 1;
	else if(height_value <= th_arr[2])
	 level_value = 2;
	else
		level_value = 3;
	if(last_level != level_value)
	{
		// 液位变化
		ucled |= 0x02;
		led_renew();
		led2_count = 0;
		led2_state = 1;
		if(level_value > last_level)
		{
			// 液位上升
			printf("A:H%d+L%d+U\r\n", height_value, level_value);
		}
		else
			printf("A:H%d+L%d+D\r\n", height_value, level_value);
		last_level = level_value;
	}
}