
#ifndef ANTI_TEXT_H
#define ANTI_TEXT_H

#include "font.h"
#include "framebuffer.h"

const uint16_t* Text_GetCharFont(char c);
void Text_DrawChar(Framebuffer* fb, char c, int x, int y);

#endif
