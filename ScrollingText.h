
#ifndef SCROLLINGTEXT_H
#define SCROLLINGTEXT_H

#include "anti_text.h"

typedef struct ScrollingTextDuet_CallBacks {
	char (ReceiveNextChar*)(void);
	void (SendNextChar*)(char);
}ScrollingTextDuet_CallBacks;

typedef struct ScrollingTextDuet {
	char first;
	char second;
	int16_t position;
	
	ScrollingTextDuet_CallBacks callbacks;
}ScrollingTextDuet;

void ScrollingTextDuet_Init(ScrollingTextDuet* this, ScrollingTextDuet_CallBacks* callbacks);

void ScrollingTextDuet_Update(ScrollingTextDuet* this);

void ScrollingTextDuet_Display(ScrollingTextDuet* this, Framebuffer* fb);

#endif
