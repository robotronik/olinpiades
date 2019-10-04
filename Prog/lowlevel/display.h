#ifndef DISPLAY_H
#define DISPLAY_H

#include "stm32f3xx_hal.h"
#include "sprites.h"

extern volatile int refresh;

void wait_refresh(void);
/**
 * Attend jusqu'à ce qu'un rafraîchissement de l'écran soit
 * nécessaire, c'est à dire jusqu'à ce que refresh soit égal à 1.
 */

void blank_screen();

void display_score(uint16_t score);

#endif
