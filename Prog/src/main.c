#include "main.h"
#include "stm32f3xx_hal.h"
#include "main_hal.h"

#include "write_matrix.h"
#include "udelay.h"

#define nbrframes 112

int main(void)
{
   // Reset of all peripherals, Initializes the Flash interface and the Systick.
  HAL_Init();
   // Configure the system clock
  SystemClock_Config();
  // Initialize all configured peripherals
  MX_GPIO_Init();
  MX_USART2_UART_Init();


  uint8_t data = 0;
  uint8_t frame[32][32];

  for (uint8_t f_number = 0 ; 1 ; f_number = (f_number + 1) % nbrframes) {
    data = f_number;
    uart_transmit_char(data);

    // mise_un_oeil(frame);
    /*
    mise_zero_oeil(frame);
    quart_cercle(frame);
    symetrie_centrale_4(frame);
    iris_cercle(
      frame,
      (f_number < nbrframes ? f_number : 2 * nbrframes - f_number) + 8,
      (f_number < nbrframes ? f_number : 2 * nbrframes - f_number) + 8,
      2
    );
    */

    //oeil_complet(frame, ((f_number<nbrframes)?f_number:(2*nbrframes-f_number))+8, 3);
    //crane_complet(frame,2);
    animation(frame, f_number);

    write_matrix(frame);
  }

  return 0;
}
