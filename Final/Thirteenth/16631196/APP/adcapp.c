#include "adcapp.h"

uint32_t adc_buffer[30] = {0};
float adc_pa4 = 0.0f, adc_pa5 = 0.0f;
float adc_pa4_real = 0.0f, adc_pa5_real = 0.0f;

void adc_init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc2, adc_buffer, 30);
}

void adc_proc(void)
{
	float temp1 = 0.0f, temp2 = 0.0f;
	for(int i = 0; i < 30; ++i)
	{
		if(i % 2 == 0)
			temp1 += adc_buffer[i];
		else
			temp2 += adc_buffer[i];
	}
	adc_pa4 = temp1 * 3.3f / 4096.0f / 15.0f;
	adc_pa5 = temp2 * 3.3f / 4096.0f / 15.0f;
}