#include "uartapp.h"

void uart_proc(void)
{
	if(!uart_rx_buffer_size) return;
	
//	printf("%s", uart_rx_buffer);
	if(uart_rx_buffer[0] == 'W')
	{
		write_eeprom();
	}
	else if(uart_rx_buffer[0] == 'R')
	{
		read_eeprom();
	}
	else if(uart_rx_buffer[0] == 'S')
	{
		dac_set_value();
	}
	
	uart_rx_buffer_size = 0;
//	memset(uart_rx_buffer, 0, uart_rx_buffer_size);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart_rx_buffer, 100);
	__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
}