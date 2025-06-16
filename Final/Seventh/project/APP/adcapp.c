#include "adcapp.h"

uint32_t adc_buffer[30] = {0};
float adc_value = 0.0f;
int temper_value = 0;

void adc_init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc2, adc_buffer, 30);
}

void adc_proc(void)
{
	float temp = 0.0f;
	for(int i = 0; i < 30; i += 3)
	{
		temp += adc_buffer[i];
	}
	adc_value = temp * 3.3f / 40960.0f;
	
	// adc范围：0~3.3
	// 温度范围: -20~60
	// y = (y2 - y1) / (x2 - x1) * (x - x1) + y1
	temper_value = (int)(80 * adc_value / 3.3f) - 20;
	
	if(temper_value > th_temper && led1_state == 0)
	{
		ucled |= 0x01;
		led_renew();
		led1_state = 1;
	}
	else if(temper_value < th_temper && led1_state == 1)
	{
		ucled &= 0xfe;
		led_renew();
		led1_state = 0;
	}
}