#include "adcapp.h"

float adc_value = 0.0f;
float k_value = 0.1f;
uint8_t led1_state = 0;

void adc_init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
	HAL_ADC_Start(&hadc2);
	HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
	adc_value = HAL_ADC_GetValue(&hadc2) * 3.3f / 4096;
}

void adc_porc(void)
{
	HAL_ADC_Start(&hadc2);
	HAL_ADC_PollForConversion(&hadc2, HAL_MAX_DELAY);
	adc_value = HAL_ADC_GetValue(&hadc2) * 3.3f / 4096;
	
	if(lcd_view == 0)
	{
		// LCD显示界面下
		sprintf(lcd_buffer, "%.2fV", adc_value);
		lcd_disp(Line0, 4, 9);
	}
	if(led1_switch)
	{
		if(adc_value > 3.3f * k_value && !led1_state)
		{
			led1_state = 1;
			ucled |= 0x01;
			led_renew();
		}
		else if(adc_value < 3.3f * k_value && led1_state)
		{
			led1_state = 0;
			ucled &= 0xfe;
			led_renew();
		}
	}
}