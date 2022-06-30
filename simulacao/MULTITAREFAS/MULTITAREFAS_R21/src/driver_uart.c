#include "driver_uart.h"
#define MODULE_LENGHT 1

struct usart_config config_usart[MODULE_LENGHT];
struct usart_module usart_instance[MODULE_LENGHT];

void uart_config(uint8_t uart_num, uint8_t uart_baudrate){
	if (uart_num <= MODULE_LENGHT-1){
		
		usart_get_config_defaults(&config_usart[uart_num]);

		config_usart[uart_num].baudrate = uart_baudrate;
		config_usart[uart_num].mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
		config_usart[uart_num].pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
		config_usart[uart_num].pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
		config_usart[uart_num].pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
		config_usart[uart_num].pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;

		while (usart_init(&usart_instance[uart_num],
				EDBG_CDC_MODULE, &config_usart[uart_num]) != STATUS_OK) {
		}
		usart_enable(&usart_instance[uart_num]);
		stdio_serial_init(&usart_instance[uart_num],EDBG_CDC_MODULE,&config_usart[uart_num]);
	}
}

void uart_transmite (uint8_t send){
	printf("%d",send);
}

void uart_recebe (uint8_t uart_num, uint8_t * recieve){
	usart_instance[uart_num].receiver_enabled = true;
	scanf("%d",&recieve);
	usart_instance[uart_num].receiver_enabled = false;
}
