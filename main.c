#include "text.h"

//#include "framebuffer.h"
#include "sprite.h"


const Sprite sprt = {
{
0b0000001100000000,
0b0001111111100000,
0b0010000000000000,
0b0000011111000000,
0b0000100000100000,
0b0001000110010000,
0b0001001111010000,
0b0001000110010000,
0b0000100000100000,
0b0000011111000000,
},10
};

int main()
{
	Framebuffer fb;
	Framebuffer_Init(&fb);
	
	//Framebuffer_Draw(&fb);

	while(1)
	{
		Sprite_Draw(&fb, &sprt, 0, 0);
		Framebuffer_Draw_Compatibility(&fb);
		sleep(0.1);
	}
	
	return 0;
}
