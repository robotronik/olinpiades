
#include "anti_text.h"

const uint16_t* Text_GetCharFont(char c) {
	return font16_ascii+(c-32)*16;
}

void Text_DrawChar(Framebuffer* fb, char c, int x, int y) {
	const uint16_t* charfont = Text_GetCharFont(c);
	uint16_t heighttodraw = 16;
	uint16_t firstlinetodraw_onframebuffer = 0;
	uint16_t firstlinetodraw_fromsprite = 0;
	
	if ( y < -16 || y > 16 || x < -16 || x > 16 ) return;
	
	if ( y < 0 ) 
	{
		// the sprite is higher than the windows framebuffer
		// clip it
		firstlinetodraw_fromsprite += -y; // new beginning
		heighttodraw -= -y; // new size
	}
	else
	{
		// the sprite is in the windows framebuffer, but can cross lower boundaries this time
		// clip it
		firstlinetodraw_onframebuffer += y;
		if ( y + heighttodraw > 16 )
			heighttodraw = 16 - y;
	}
	
	
	if ( x > 0) {
		uint8_t shift = x;
		for(uint16_t y = 0; y<heighttodraw; y++)
			fb->data[y + firstlinetodraw_onframebuffer] |= charfont[y + firstlinetodraw_fromsprite] >> shift;
			}
	else {
		uint8_t shift = -x;
		for(uint16_t y = 0; y<heighttodraw; y++)
			fb->data[y + firstlinetodraw_onframebuffer] |= charfont[y + firstlinetodraw_fromsprite] << shift;
	}
}



