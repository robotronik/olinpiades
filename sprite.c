
#include "sprite.h"

void Sprite_Draw(Framebuffer* fb, const Sprite* sp, int x, int y) {
	uint16_t heighttodraw = sp->height;
	uint16_t firstlinetodraw_onframebuffer = 0;
	uint16_t firstlinetodraw_fromsprite = 0;
	
	if ( y < -16 || y > 16 || x < -16 || x > 16 ) return;
	
	if ( y < 0 ) 
	{
		// the sprite is higher than the windows framebuffer
		//   xxxx
		//  -xxxx--------    see? :)
		//  |xxxx       |
		//  |xxxx       |
		//  |           |
		//  |           |
		//  -------------
		// clip it
		firstlinetodraw_fromsprite += -y; // new beginning
		heighttodraw -= -y; // new size
	}
	else
	{
		// the sprite is in the windows framebuffer, but can cross lower boundaries this time
		// 
		//  -------------  
		//  |           |
		//  |           |
		//  |           |
		//  |xxxx       |
		//  -xxxx--------
		//   xxxx
		//
		// clip it
		firstlinetodraw_onframebuffer += y;
		if ( y + heighttodraw > 16 )
			heighttodraw = 16 - y;
	}
	
	
	if ( x > 0) {
		uint8_t shift = x;
		for(uint16_t y = 0; y<heighttodraw; y++)
			fb->data[y + firstlinetodraw_onframebuffer] |= sp->pdata[y + firstlinetodraw_fromsprite] >> shift;
			}
	else {
		uint8_t shift = -x;
		for(uint16_t y = 0; y<heighttodraw; y++)
			fb->data[y + firstlinetodraw_onframebuffer] |= sp->pdata[y + firstlinetodraw_fromsprite] << shift;
	}
	
}

void Sprite_DrawWithClipping(Framebuffer* fb, const Framebuffer* fbclip, const Sprite* sp, int x, int y) {
	uint16_t heighttodraw = sp->height;
	uint16_t firstlinetodraw_onframebuffer = 0;
	uint16_t firstlinetodraw_fromsprite = 0;
	
	if ( y < -16 || y > 16 || x < -16 || x > 16 ) return;
	
	if ( y < 0 ) 
	{
		firstlinetodraw_fromsprite += -y; // new beginning
		heighttodraw -= -y; // new size
	}
	else
	{
		firstlinetodraw_onframebuffer += y;
		if ( y + heighttodraw > 16 )
			heighttodraw = 16 - y;
	}
	
	
	if ( x > 0) {
		uint8_t shift = x;
		for(uint16_t y = 0; y<heighttodraw; y++)
			fb->data[y + firstlinetodraw_onframebuffer] |= fbclip->data[y + firstlinetodraw_onframebuffer] & (sp->pdata[y + firstlinetodraw_fromsprite] >> shift);
			}
	else {
		uint8_t shift = -x;
		for(uint16_t y = 0; y<heighttodraw; y++)
			fb->data[y + firstlinetodraw_onframebuffer] |= fbclip->data[y + firstlinetodraw_onframebuffer] & (sp->pdata[y + firstlinetodraw_fromsprite] << shift);
	}
	
}

