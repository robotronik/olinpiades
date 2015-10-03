#include "text.h"

#include <stdlib.h>
//#include "framebuffer.h"
#include "sprite.h"

typedef enum SoftTimer_Direction {
	Up,
	Down
}SoftTimer_Direction;

typedef struct SoftTimer {
	uint32_t phacc;
	int16_t phadd;
}SoftTimer;

void SoftTimer_Init(SoftTimer* st) {
	st->phacc = 0; st->phadd = 0;
}
void SoftTimer_Setphadd(SoftTimer* st, int8_t add) {
	st->phadd = add;
}
void SoftTimer_SetDir(SoftTimer* st, SoftTimer_Direction dir) {
	if ( dir == Up ) st->phacc = abs(st->phacc);
	else st->phacc = -abs(st->phacc);
}
uint8_t SoftTimer_Get8bValue(SoftTimer* st) {
	return st->phacc >> 8;
}
void SoftTimer_Update(SoftTimer* st) {
	
	st->phacc += st->phadd;
}


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
	uint16_t currentkey;
	SoftTimer timer;
	KeyList* keylist;
}KeyAnimation;

void KeyAnimation_Init(KeyAnimation* ka, KeyList* keylist) {
	ka->currentkey = 0;
	ka->keylist = keylist;
	SoftTimer_Init(&(ka->timer));
}

void KeyAnimation_Update(KeyAnimation* ka) {
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
9,
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
	Sprite_Draw(&fb, &uglyeye, -2, -4);
	Sprite_Draw(&fb, &uglyeye, -2, 6);
	Sprite_Draw(&fb, &uglyeye, 8, 8);
	Framebuffer_Draw(&fb);
}
