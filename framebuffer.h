#ifndef FRAMEBUFFER8H
#define FRAMEBUFFER_H

#include <stdint.h>
#include <stdio.h>
#include "hardware.h"

#define FB_WIDTH_PIX 	16
#define FB_HEIGHT_PIX 16

#define FB_HEIGHT_SHORT 	(FB_WIDTH_PIX / 16)
#define FB_WIDTH_SHORT (FB_HEIGHT_PIX)

typedef struct {
	uint16_t data[FB_WIDTH_SHORT * FB_HEIGHT_SHORT];
}Framebuffer;

void Framebuffer_Init(Framebuffer* fb);
void Framebuffer_Draw(Framebuffer* fb);
void Framebuffer_Draw_Compatibility(Framebuffer* fb);
void Framebuffer_Clear(Framebuffer* fb);

#endif
