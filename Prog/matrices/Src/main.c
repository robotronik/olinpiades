#include "main.h"
#include "stm32f3xx_hal.h"

#include "udelay.h"

#define nbrframes 112


// Private variables ---------------------------------------------------------
UART_HandleTypeDef huart2;

// Private function prototypes -----------------------------------------------
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);


int main(void)
{
   // Reset of all peripherals, Initializes the Flash interface and the Systick.
  HAL_Init();
   // Configure the system clock
  SystemClock_Config();

  // Initialize all configured peripherals
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  uint8_t f_number = 0;
  uint8_t data[1] = {0};
  char frame[32][32];

  while (1)
  {
    data[0] = f_number;
    HAL_UART_Transmit_IT(&huart2, data, 1);

    //mise_un_oeil(frame);
    /*mise_zero_oeil(frame);
    quart_cercle(frame);
    symetrie_centrale_4(frame);
    iris_cercle(frame,((f_number<nbrframes)?f_number:(2*nbrframes-f_number))+8,((f_number<nbrframes)?f_number:(2*nbrframes-f_number))+8,2);*/

    //oeil_complet(frame, ((f_number<nbrframes)?f_number:(2*nbrframes-f_number))+8, 3);
    //crane_complet(frame,2);
    animation(frame, f_number);

    write_matrix(frame);

    f_number = (f_number + 1) % nbrframes;
  }

  return 0;
}
