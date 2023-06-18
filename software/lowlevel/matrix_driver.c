#include "matrix_driver.h"

#include "clock.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define BLANK_Port_Lin     GPIOA
#define BLANK_Pin_Lin           GPIO0
#define BLANK_Port_Col     GPIOA
#define BLANK_Pin_Col           GPIO1
#define SERIAL_IN_Port_Lin GPIOB
#define SERIAL_IN_Pin_Lin       GPIO7
#define SERIAL_IN_Port_Col1 GPIOA
#define SERIAL_IN_Pin_Col1       GPIO8
#define CLK_Port_Col   GPIOA
#define CLK_Pin_Col         GPIO11
#define CLK_Port_Lin   GPIOB
#define CLK_Pin_Lin         GPIO6
#define LATCH_Port_Col GPIOA
#define LATCH_Pin_Col       GPIO12
#define LATCH_Port_Lin GPIOB
#define LATCH_Pin_Lin       GPIO5
#define CLEAR_Port_Lin GPIOA
#define CLEAR_Pin_Lin       GPIO4
#define CLEAR_Port_Col GPIOB
#define CLEAR_Pin_Col       GPIO1


const int boucleframe = 4000;

void led_driver_setup() {
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB);

  gpio_mode_setup(BLANK_Port_Lin,     GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, BLANK_Pin_Lin);
  gpio_mode_setup(BLANK_Port_Col,     GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, BLANK_Pin_Col);
  gpio_mode_setup(SERIAL_IN_Port_Lin,      GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SERIAL_IN_Pin_Lin);
  gpio_mode_setup(SERIAL_IN_Port_Col1,    GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SERIAL_IN_Pin_Col1);
  gpio_mode_setup(CLK_Port_Col,    GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, CLK_Pin_Col);
  gpio_mode_setup(CLK_Port_Lin, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, CLK_Pin_Lin);
  gpio_mode_setup(LATCH_Port_Col,   GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LATCH_Pin_Col);
  gpio_mode_setup(LATCH_Port_Lin, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LATCH_Pin_Lin);
  gpio_mode_setup(LATCH_Port_Col,   GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LATCH_Pin_Col);
  gpio_mode_setup(LATCH_Port_Lin, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LATCH_Pin_Lin);
  gpio_mode_setup(CLEAR_Port_Lin,   GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, CLEAR_Pin_Lin);
  gpio_mode_setup(CLEAR_Port_Col, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, CLEAR_Pin_Col);

  gpio_set(CLEAR_Port_Lin, CLEAR_Pin_Lin);
  gpio_set(CLEAR_Port_Col, CLEAR_Pin_Col);
  gpio_clear(BLANK_Port_Lin, BLANK_Pin_Lin);
  gpio_clear(BLANK_Port_Col, BLANK_Pin_Col);
}

void gpio_set_int(uint32_t gpioport, uint16_t gpios, int value) {
  (value & 1) ? gpio_set(gpioport, gpios) : gpio_clear(gpioport, gpios);
}



void select_line(uint32_t line) {
  // Sélection de la ligne
  gpio_clear(LATCH_Port_Col, LATCH_Pin_Col);
  gpio_clear(CLK_Port_Col, CLK_Pin_Col);
  if(line==0){
    gpio_set(SERIAL_IN_Port_Col1,SERIAL_IN_Pin_Col1);
  }
  else{
    gpio_clear(SERIAL_IN_Port_Col1,SERIAL_IN_Pin_Col1);
  }
  gpio_set  (CLK_Port_Col, CLK_Pin_Col);
}


void send_Col(uint32_t line) {
  gpio_clear(LATCH_Port_Lin, LATCH_Pin_Lin);

  for (int col = 0; col < 32; ++col) {
    gpio_clear(CLK_Port_Lin, CLK_Pin_Lin);
    gpio_set_int(SERIAL_IN_Port_Lin, SERIAL_IN_Pin_Lin, 1-(line >> (31-col)));
    gpio_set  (CLK_Port_Lin, CLK_Pin_Lin);
    
  }

  
}

void display_matrix_once(uint32_t matrix[MATRIX_SIZE]) {
  for (int line = 0; line < MATRIX_SIZE; ++line) {

    send_Col(matrix[line]);

    select_line(line);

    gpio_set(BLANK_Port_Col,BLANK_Pin_Col);
    delay_us(30);
    gpio_set(LATCH_Port_Lin, LATCH_Pin_Lin);
    gpio_set(LATCH_Port_Col, LATCH_Pin_Col);
    delay_us(10);
    gpio_clear(BLANK_Port_Col,BLANK_Pin_Col);
    
    
    



    
    //delay_ms(1);
    delay_us(100);
  }
}

void display_matrix(uint32_t matrix[MATRIX_SIZE],int frame_count) {
  for(int k = 0; k < frame_count; ++k) {
    display_matrix_once(matrix);
    delay_us(20);
  }
}
