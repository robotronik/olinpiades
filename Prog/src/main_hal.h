#pragma once

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);

void uart_transmit_char(unsigned char c);
