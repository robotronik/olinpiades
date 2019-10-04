#include "matrix_driver.h"

#define PURGE_Port     GPIOA
#define PURGE_Pin           GPIO0
#define BLANK_Port     GPIOA
#define BLANK_Pin           GPIO1
#define DATA_Port      GPIOA
#define DATA_Pin            GPIO4
#define LINE_0_Port    GPIOB
#define LINE_0_Pin          GPIO1
#define LINE_1_Port    GPIOB
#define LINE_1_Pin          GPIO0
#define LINE_2_Port    GPIOA
#define LINE_2_Pin          GPIO7
#define LINE_3_Port    GPIOA
#define LINE_3_Pin          GPIO6
#define LINE_4_Port    GPIOA
#define LINE_4_Pin          GPIO5
#define SERIAL_IN_Port GPIOA
#define SERIAL_IN_Pin       GPIO10
#define CLK_COL_Port   GPIOA
#define CLK_COL_Pin         GPIO11
#define LATCH_COL_Port GPIOA
#define LATCH_COL_Pin       GPIO12


const int boucleframe = 40;

void led_driver_setup() {
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB);

  gpio_mode_setup(PURGE_Port,     GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PURGE_Pin);
  gpio_mode_setup(BLANK_Port,     GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, BLANK_Pin);
  gpio_mode_setup(DATA_Port,      GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, DATA_Pin);
  gpio_mode_setup(LINE_0_Port,    GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LINE_0_Pin);
  gpio_mode_setup(LINE_1_Port,    GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LINE_1_Pin);
  gpio_mode_setup(LINE_2_Port,    GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LINE_2_Pin);
  gpio_mode_setup(LINE_3_Port,    GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LINE_3_Pin);
  gpio_mode_setup(LINE_4_Port,    GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LINE_4_Pin);
  gpio_mode_setup(SERIAL_IN_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SERIAL_IN_Pin);
  gpio_mode_setup(CLK_COL_Port,   GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, CLK_COL_Pin);
  gpio_mode_setup(LATCH_COL_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LATCH_COL_Pin);
}

void gpio_set_int(uint32_t gpioport, uint8_t gpios, int value) {
  (value & 1) ? gpio_set(gpioport, gpios) : gpio_clear(gpioport, gpios);
}

void capa_purge_on() {
  gpio_set(DATA_Port, DATA_Pin);
  gpio_set(BLANK_Port, BLANK_Pin);
  gpio_set(PURGE_Port, PURGE_Pin);
}
void capa_purge_off() {
  gpio_clear(DATA_Port, DATA_Pin);
  gpio_clear(BLANK_Port, BLANK_Pin);
  gpio_clear(PURGE_Port, PURGE_Pin);
}

void select_line(uint32_t line) {
  // Sélection de la ligne
  gpio_set_int(LINE_0_Port, LINE_0_Pin, (line & 1) != 0);
  gpio_set_int(LINE_1_Port, LINE_1_Pin, (line & 2) != 0);
  gpio_set_int(LINE_2_Port, LINE_2_Pin, (line & 4) != 0);
  gpio_set_int(LINE_3_Port, LINE_3_Pin, (line & 8) != 0);
  gpio_set_int(LINE_4_Port, LINE_4_Pin, (line & 16) != 0);
}


void send_line(uint32_t line) {
  gpio_clear(LATCH_COL_Port, LATCH_COL_Pin);

  for (int col = 0; col < 32; ++col) {
    gpio_clear(CLK_COL_Port, CLK_COL_Pin, 0);
    gpio_set_int(SERIAL_IN_Port, SERIAL_IN_Pin, line >> col);
    gpio_set  (CLK_COL_Port, CLK_COL_Pin, 1);
  }

  gpio_set(LATCH_COL_Port, LATCH_COL_Pin);
}

void display_matrix_once(uint32_t matrix[MATRIX_SIZE]) {
  for (int line = 0; line < MATRIX_SIZE; ++line) {
    capa_purge_off();

    select_line(line);

    send_line(matrix[line]);

    capa_purge_on();
    delay_us(20);
  }
}

void display_matrix(uint32_t matrix[MATRIX_SIZE]) {
  for(int k = 0; k < boucleframe; ++k) {
    display_matrix_once(matrix);
  }
}
