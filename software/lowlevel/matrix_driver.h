#pragma once

#include <stdint.h>

void led_driver_setup();

#define MATRIX_SIZE 32

void display_matrix(uint32_t matrix[MATRIX_SIZE]);
