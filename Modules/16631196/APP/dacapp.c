#include "dacapp.h"

float dac1_value = 0.0f, dac2_value = 0.0f;

void dac_init(void)
{
	HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
	HAL_DAC_Start(&hdac1, DAC_CHANNEL_2);
}

void dac_set_value(void)
{
	HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (uint32_t)(dac1_value * 4096.0f / 3.3f));
	HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, (uint32_t)(dac2_value * 4096.0f / 3.3f));
}