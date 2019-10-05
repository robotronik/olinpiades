#include "uart.h"

#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

/***************************************
simple uart configuration for debugging
***************************************/

//DEFINES FOR DEBUG_UART
#define DEBUG_RCC_USART RCC_USART1
#define DEBUG_USART USART1
#define DEBUG_UART_SPEED (9600*2)
// Bug in libopencm3 ? Need to *2 because of APB2/APB1 weird things.

#define DEBUG_PORT_TX GPIOB
#define DEBUG_PORT_TX_RCC RCC_GPIOB // clock of GPIO port
#define DEBUG_PIN_TX GPIO6
#define DEBUG_AF_TX GPIO_AF7

#define DEBUG_PORT_RX GPIOB
#define DEBUG_PORT_RX_RCC RCC_GPIOB
#define DEBUG_PIN_RX GPIO7
#define DEBUG_AF_RX GPIO_AF7


receive_interrupt* uart_callback;
void set_receive_char_interrupt(receive_interrupt* callback) {
  uart_callback = callback;
}

void uart_setup()
{
  // Open GPIO for USART
  rcc_periph_clock_enable(DEBUG_PORT_TX_RCC);
  gpio_mode_setup(DEBUG_PORT_TX, GPIO_MODE_AF, GPIO_PUPD_NONE, DEBUG_PIN_TX);
  gpio_set_af(DEBUG_PORT_TX, DEBUG_AF_TX, DEBUG_PIN_TX);

  rcc_periph_clock_enable(DEBUG_PORT_RX_RCC);
  gpio_mode_setup(DEBUG_PORT_RX, GPIO_MODE_AF, GPIO_PUPD_NONE, DEBUG_PIN_RX);
  gpio_set_af(DEBUG_PORT_RX, DEBUG_AF_RX, DEBUG_PIN_RX);

  rcc_periph_clock_enable(DEBUG_RCC_USART);

  usart_disable(DEBUG_USART);

  usart_set_baudrate(DEBUG_USART, DEBUG_UART_SPEED);
  usart_set_databits(DEBUG_USART, 8);
  usart_set_stopbits(DEBUG_USART, USART_STOPBITS_1);
  usart_set_mode(DEBUG_USART, USART_MODE_TX_RX);
  usart_set_parity(DEBUG_USART, USART_PARITY_NONE);
  usart_set_flow_control(DEBUG_USART, USART_FLOWCONTROL_NONE);

  usart_enable(DEBUG_USART);
}

void echo(char *chain)
{
  int i, n=0;
  while(chain[n]!='\0') n++;
  for(i=0;i<n;i++) usart_send_blocking(DEBUG_USART, chain[i]);
}

void echo_int(int integer)
{
	int i=0,po=0,integer_tmp=integer;
	char chain[256],*chain_tmp;

	if(integer<0)//add - before if negative number
	{
		chain[0]='-';
		chain_tmp=&chain[1];
		integer=-integer;//absolute value
	}
	else
	{
		chain_tmp=chain;
	}
	//the power of ten of the number
	do{
		integer_tmp/=10;
		po++;
	}while(integer_tmp!=0);

	do{//converting the integer to caracters
		chain_tmp[po-i-1]=(integer%10)+'0';
		i++;
		integer=integer/10;
	}while(integer!=0);

	chain_tmp[i]='\0';//end of number line
	echo(chain);//finally prints the number
}
