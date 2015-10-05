
#ifndef SPRITE_H
#define SPRITE_H

#include <stdint.h>
#include <stdio.h>
#include "framebuffer.h"

typedef struct {
	uint8_t height;
	uint16_t pdata[]; // 16xheight pixel sprite
}Sprite;

void Sprite_Draw(Framebuffer* fb, const Sprite* sp, int x, int y);
void Sprite_DrawWithClipping(Framebuffer* fb, const Framebuffer* fbclip, const Sprite* sp, int x, int y);

#endif
