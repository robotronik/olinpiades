#include "text.h"

//#include "framebuffer.h"
#include "sprite.h"

typedef enum SoftTimer_Direction {
	Up,
	Down
}SoftTimer_Direction;

typedef struct SoftTimer {
	uint16_t phacc;
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
void SoftTimer_Get8bValue(SoftTimer* st) {
	return st->phacc >> 8;
}
void SoftTimer_Update(SoftTimer* st) {
	
	st->phacc += st->phadd;
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

int main(int argc, char** args)
{
	Framebuffer fb;
	Framebuffer_Init(&fb);
	
	int x = -4;
	int dx = 0;
	int y = 3; 
	Sprite_Draw(&fb, &uglyeye, -2, 1);
	Sprite_Draw(&fb, &uglyeye, 6, 6);
	Framebuffer_Draw(&fb);
}
