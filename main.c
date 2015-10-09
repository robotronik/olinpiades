
#include <stdlib.h>
#include "eyedevil.h"
#include "anti_text.h"
#include "hardware.h"

void Demo_EyeDevil(Framebuffer* fb);


int main(void)
{
	init_hardware();

	//Framebuffer fb;
	//Framebuffer_Init(&fb);
	

	Framebuffer fb;
	Framebuffer_Init(&fb);


	for(int i=0; i<16; i++){
		fb.data[i] = 1 << i;
	}

	Framebuffer_Clear(&fb);

	Sprite_Draw(&fb, &eye_pupil, -5, -5);

	Demo_EyeDevil(&fb);

	///pause_ms(200);
	while(1)
	{
		for (int i = 0; i < 16; ++i)
		{
			write_column(i+1, fb.data[i]);
		}
	}
	/*
	
	Demo_EyeDevil(&fb);*/
}
