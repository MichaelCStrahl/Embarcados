#include <asf.h>

void uart_config(uint8_t uart_num, uint8_t uart_baudrate);

void uart_transmite (uint8_t send);

void uart_recebe (uint8_t uart_num, uint8_t * recieve);