
#include "ScrollingText.h"

void ScrollingTextDuet_Init(ScrollingTextDuet* this, ScrollingTextDuet_CallBacks* callbacks, void* object) {
	this->first = ' ';
	this->second = ' ';
	this->positionfirst = 0;                
}
                            
void ScrollingTextDuet_Update(ScrollingTextDuet* this) {

	// increment first char position;
	if ( this->positionfirst++ == -16) {
		// first char disappeared completely
		// first char becomes second char
		this->first = this->second;
		// send second char as it is about to get offscreen on this display and will start to appear 	on the next display.
		(*this->callbacks.SendNextChar)(this->callbacks.object, this->second);
		// query the new second char
		this->second = (*this->callbacks.ReceiveNextChar)(this->callbacks.object);
		this->positionfirst = 0;
	} 
}

void ScrollingTextDuet_Display(const ScrollingTextDuet* this, Framebuffer* fb) {
	Text_DrawChar(Framebuffer* fb, this->first, this->positionfirst , 0);
	Text_DrawChar(Framebuffer* fb, this->second, this->positionfirst + 16, 0);
}
