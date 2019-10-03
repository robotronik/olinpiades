#include "write_matrix.h"
#include "main.h"
#include "udelay.h"

#include "stm32f3xx_hal.h"

#define boucleframe 40

void write_matrix_once(uint8_t matrix[GF][GF]) {
  for(int i = 0; i < 32; i++) {
    // purge des capas essayer sans
    HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, 1);
    HAL_GPIO_WritePin(BLANK_GPIO_Port, BLANK_Pin, 1);
    HAL_GPIO_WritePin(PURGE_GPIO_Port, PURGE_Pin, 1);

    // sélection de la colonne
    HAL_GPIO_WritePin(LINE_0_GPIO_Port, LINE_0_Pin, (i & 1) != 0);
    HAL_GPIO_WritePin(LINE_1_GPIO_Port, LINE_1_Pin, (i & 2) != 0);
    HAL_GPIO_WritePin(LINE_2_GPIO_Port, LINE_2_Pin, (i & 4) != 0);
    HAL_GPIO_WritePin(LINE_3_GPIO_Port, LINE_3_Pin, (i & 8) != 0);
    HAL_GPIO_WritePin(LINE_4_GPIO_Port, LINE_4_Pin, (i & 16) != 0);

    // sélection des leds
    HAL_GPIO_WritePin(LATCH_COL_GPIO_Port, LATCH_COL_Pin, 0);
    for(int j = 0; j < 32; j++) {
      HAL_GPIO_WritePin(CLK_COL_GPIO_Port, CLK_COL_Pin, 0);
      HAL_GPIO_WritePin(SERIAL_IN_GPIO_Port, SERIAL_IN_Pin, matrix[i][31-j]);
      HAL_GPIO_WritePin(CLK_COL_GPIO_Port, CLK_COL_Pin, 1);
    }
    HAL_GPIO_WritePin(LATCH_COL_GPIO_Port, LATCH_COL_Pin, 1);

    // réactivation
    HAL_GPIO_WritePin(PURGE_GPIO_Port, PURGE_Pin, 0);
    HAL_GPIO_WritePin(BLANK_GPIO_Port, BLANK_Pin, 0);
    HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, 0);

    udelay(20);
  }
}


void write_matrix(uint8_t matrix[GF][GF]) {
  for(int k = 0; k < boucleframe; ++k) {
    write_matrix_once(matrix);
  }
}
