
#ifndef SPRITE_H
#define SPRITE_H

#include <stdint.h>
#include <stdio.h>
#include "framebuffer.h"

typedef struct {
	uint16_t pdata[16]; // 16x16 pixel sprite
	uint8_t height;
}Sprite;

void Sprite_Draw(Framebuffer* fb, Sprite* sp, int x, int y);

#endif
