
#ifndef SCROLLINGTEXT_H
#define SCROLLINGTEXT_H

#include "anti_text.h"

typedef Struct ScrollingText;

///
/// ScrollingTextDuet
///
typedef struct ScrollingTextDuet {
	char first;
	char second;
	int16_t positionfirst;
	ScrollingText* scrollingText;
}ScrollingTextDuet;

void ScrollingTextDuet_Init(ScrollingTextDuet* this, ScrollingText* scrollingText);
                            
void ScrollingTextDuet_Update(ScrollingTextDuet* this);

void ScrollingTextDuet_Display(const ScrollingTextDuet* this, Framebuffer* fb);

///
/// ScrollingText
///

#define CHARBUFFER_SIZE 128

typedef struct CharBuffer {
	char c[CHARBUFFER_SIZE];
	char* ptr_read;
	char* ptr_write;
};

void CharBuffer_Init(CharBuffer* this);

void CharBuffer_PutChar(CharBuffer* this, char c);
void CharBuffer_AppendString(CharBuffer* this, char* str);




typedef Struct ScrollingText {
	const char* string;
	const char* stringptr;
}ScrollingText;

void Callback

void ScrollingText_Init(ScrollingText* this, const char* string);

void ScrollingText_Update(ScrollingText* this);

void ScrollingText_Display(ScrollingText* this);

#endif


