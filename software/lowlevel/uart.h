#pragma once

#include <stdint.h>

void uart_setup(void);
void echo(char* chain);
void echo_int(int integer);

typedef void (receive_interrupt(uint8_t));
void set_receive_char_interrupt(receive_interrupt* callback);

//rec=usart_recv_blocking(DEBUG_USART);//to receive a byte
