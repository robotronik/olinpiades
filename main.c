#include "text.h"

#include <stdlib.h>
//#include "framebuffer.h"
#include "sprite.h"


typedef enum Key_Type {
	Constant,
	Linear
}Key_Type;

typedef struct Key {
	int16_t value;
	uint16_t duration;
	Key_Type type;;
}Key;

typedef struct KeyList {
	uint16_t size;
	Key key[];
}KeyList;

typedef struct KeyAnimation {
	uint16_t currentkeyindex;
	uint16_t nextkeyindex;
	uint16_t durationcounter;
	KeyList* keylist;
}KeyAnimation;

void KeyAnimation_Init(KeyAnimation* ka, KeyList* keylist) {
	ka->currentkeyindex = 0;
	ka->nextkeyindex = 1;
	ka->durationcounter = 0;
	ka->keylist = keylist;
}

int16_t KeyAnimation_GetCurrentValue(KeyAnimation* ka) {
	int16_t value;
	
	int16_t currentvalue = ka->keylist->key[ka->currentkeyindex].value;
	Key_Type currenttype = ka->keylist->key[ka->currentkeyindex].type;
	
	if ( currenttype == Linear ) {
		uint16_t currentduration = ka->keylist->key[ka->currentkeyindex].duration;
		int16_t nextvalue = ka->keylist->key[ka->nextkeyindex].value;
		value = currentvalue + (ka->durationcounter * (nextvalue - currentvalue)) / currentduration; 
	}
	else {
		value = currentvalue; 
	}
	return value;
}

void KeyAnimation_Update(KeyAnimation* ka) {
	ka->durationcounter++;
	if ( ka->durationcounter == ka->keylist->key[ka->currentkeyindex].duration ) {
		ka->durationcounter = 0;
		
		ka->currentkeyindex++;
		if ( ka->currentkeyindex == ka->keylist->size ) 
			ka->currentkeyindex = 0;
			
		ka->nextkeyindex++;
		if ( ka->nextkeyindex == ka->keylist->size ) 
			ka->nextkeyindex = 0;
	}
}



const Sprite uglyeye = {
9,
{
0b0111111100000000,
0b1000000000000000,
0b0011111000000000,
0b0100000100000000,
0b1000110010000000,
0b1001111010000000,
0b1000110010000000,
0b0100000100000000,
0b0011111000000000,
}
};

const Sprite woo = {
3,
{
0b1000101110111000,
0b1010101010101000,
0b1101101110111000,
}
};

int main(int argc, char** args)
{
	Framebuffer fb;
	Framebuffer_Init(&fb);
	
	int x = -4;
	int dx = 0;
	int y = 3; 
	Sprite_Draw(&fb, &woo, 1, 1);
	Sprite_Draw(&fb, &uglyeye, -2, 6);
	Sprite_Draw(&fb, &uglyeye, 8, 8);
	Framebuffer_Draw(&fb);
}
