#include "text.h"

#include <stdlib.h>
//#include "framebuffer.h"
#include "sprite.h"
#include "keyanimation.h"

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

const KeyList test_keylist = {
3,
{
{0,			10,			Linear},
{10,		10,			Linear},
{-10,		10,			Constant}
}
};

void Test_KeyAnimation(void) {
	KeyAnimation ka;
	KeyAnimation_Init(&ka, &test_keylist);
	int cnt = 0;
	while ( KeyAnimation_Update(&ka) != AnimationIsOver ) {
		cnt++;
		int16_t value = KeyAnimation_GetValue(&ka);
		printf("value(%d) = %d\n",cnt,value);
	}
}

void Test_FramebufferSprite(void) {
	Framebuffer fb;
	Framebuffer_Init(&fb);
	
	Sprite_Draw(&fb, &woo, 1, 1);
	Sprite_Draw(&fb, &uglyeye, -2, 6);
	Sprite_Draw(&fb, &uglyeye, 8, 8);
	
	Framebuffer_Draw(&fb);
}

void Test_Text(void) {
	while(1) {
	animation();
	}
}

int main(void)
{
	Test_KeyAnimation();
}











