
#include <stdlib.h>
/*#include "eyedevil.h"
#include "anti_text.h"*/
#include "hardware.h"

//void Demo_EyeDevil(Framebuffer* fb);

int main(void)
{
	init_hardware();
	pause_ms(200);
	while(1)
	{
	for(int y=0; y<16; y++) {
		write_column(y, 0xFFFF);
		pause_us(1200);
	}
}/*
	Framebuffer fb;
	Framebuffer_Init(&fb);
	
	Demo_EyeDevil(&fb);*/
}
