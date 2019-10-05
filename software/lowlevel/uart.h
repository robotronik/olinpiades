#pragma once

void uart_setup(void);
void echo(char *chain);
void echo_int(int integer);

//rec=usart_recv_blocking(DEBUG_USART);//to receive a byte
