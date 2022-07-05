#include "driver_uart.h"
#define MODULE_LENGHT 1

struct usart_module usart_instance[MODULE_LENGHT];
struct usart_config usart_conf[MODULE_LENGHT];

void uart_config(uint8_t uart_num, uint8_t uart_baudrate){
	if (uart_num <= MODULE_LENGHT-1){
		
		usart_get_config_defaults(&usart_conf[uart_num]);
		usart_conf[uart_num].baudrate    = uart_baudrate;
		usart_conf[uart_num].mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
		usart_conf[uart_num].pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
		usart_conf[uart_num].pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
		usart_conf[uart_num].pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
		usart_conf[uart_num].pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
		
		stdio_serial_init(&usart_instance[uart_num], EDBG_CDC_MODULE, &usart_conf[uart_num]);
		
		usart_instance[uart_num].transmitter_enabled = true;
		usart_enable(&usart_instance[uart_num]);
		
	}
}

void uart_transmite(uint8_t uart_num){
	usart_serial_putchar(&usart_instance[uart_num],'a');
}

void uart_recebe (uint8_t uart_num, uint8_t * recieve){
	scanf("%d",&recieve);
}
