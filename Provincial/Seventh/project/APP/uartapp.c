#include "uartapp.h"

void uart_proc(void)
{
	if(!uart_buffer_size) return;
	
	if(uart_buffer_size == 1 && uart_rx_buffer[0] == 'C')
	{
		printf("C:H%d+L%d\r\n", height_value, level_value);
		// 查询
		ucled |= 0x04;
		led_renew();
		led3_count = 0;
		led3_state = 1;
	}
	else if(uart_buffer_size == 1 && uart_rx_buffer[0] == 'S')
	{
		printf("S:TL%d+TM%d+TH%d\r\n", th_arr[0], th_arr[1], th_arr[2]);
		// 查询
		ucled |= 0x04;
		led_renew();
		led3_count = 0;
		led3_state = 1;
	}
	
	memset(uart_rx_buffer, 0, uart_buffer_size);
	uart_buffer_size = 0;
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart_rx_buffer, sizeof(uart_rx_buffer));
	__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
}