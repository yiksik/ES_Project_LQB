#include "ledapp.h"

uint8_t ucled = 0x10;

void led_renew(void)
{
	HAL_GPIO_WritePin(GPIOC, 0XFF00, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, (ucled << 8), GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
}