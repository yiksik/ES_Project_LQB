#include "adcapp.h"

uint32_t adc1_buffer[30] = {0};
uint32_t adc2_buffer[30] = {0};
float adc1_r38_value = 0.0f, adc2_r37_value = 0.0f, adc1_mcp_value = 0.0f;

void adc_init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc1, adc1_buffer, 30);
	HAL_ADC_Start_DMA(&hadc2, adc2_buffer, 30);
}

void adc_proc(void)
{
	float temp1 = 0.0f, temp2 = 0.0f, temp3 = 0.0f;
	for(int i = 0; i < 30; i ++)
	{
		if(i%2)
			temp3 += adc1_buffer[i];
		else
			temp1 += adc1_buffer[i];
		temp2 += adc2_buffer[i];
	}
	adc1_r38_value = temp1 * 3.3f / 4096.0f / 15.0f;
	adc2_r37_value = temp2 * 3.3f / 4096.0f / 30.0f;
	adc1_mcp_value = temp3 * 3.3f / 4096.0f / 15.0f;
}