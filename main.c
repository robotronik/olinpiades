#include "text.h"

#include <stdlib.h>
//#include "framebuffer.h"
#include "sprite.h"
#include "keyanimation.h"

const Sprite uglyeye = {
9,
{
0b0111111110000000,
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
{0,10,Linear},
{10,10,Linear},
{-10,10,Constant}
}
};

const KeyList test_keylist_x = {
3,
{
{-3,10,Linear},
{5,10,Linear},
{9,30,Linear}
}
};

const KeyList test_keylist_y = {
3,
{
{-2,10,Linear},
{11,10,Linear},
{4,30,Linear}
}
};


const KeyList test_keylist_wave = {
2,
{
{8,7,Linear},
{11,3,Linear},
}
};

void Test_FramebufferSpriteKeyAnimation(void) {
	// create and init a framebuffer
	Framebuffer fb;
	Framebuffer_Init(&fb);
	
	// load an xy animation 
	KeyAnimation ka_x, ka_y, ka_w;
	KeyAnimation_Init(&ka_x, &test_keylist_x);
	KeyAnimation_Init(&ka_y, &test_keylist_y);
	KeyAnimation_Init(&ka_w, &test_keylist_wave);
	
	while (1) {
		usleep(40000);
		KeyAnimation_Update(&ka_x);
		KeyAnimation_Update(&ka_y);
		KeyAnimation_Update(&ka_w);
		int16_t x = KeyAnimation_GetValue(&ka_x);
		int16_t y = KeyAnimation_GetValue(&ka_y);
		int16_t w = KeyAnimation_GetValue(&ka_w);
		Framebuffer_Clear(&fb);
		Sprite_Draw(&fb, &uglyeye, x, y);
		Sprite_Draw(&fb, &woo, 1, w);
		Framebuffer_Draw(&fb);
	}
}

void Test_KeyAnimation_void(void) {
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
	Test_FramebufferSpriteKeyAnimation();
}











