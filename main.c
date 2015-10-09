
#include <stdlib.h>
#include "eyedevil.h"
#include "anti_text.h"
#include "hardware.h"

void Demo_EyeDevil(Framebuffer* fb);
Framebuffer fb;

int main(void)
{
	init_hardware();
	Framebuffer_Init(&fb);
	Demo_EyeDevil(&fb);

	Framebuffer_Draw(&fb);
	pause_ms(200);
	while(1)
	{
	for(int y=1; y<=16; y++) {
		write_column(y, 0b1<<(y-1));
		pause_us(3200);
	}
}/*
	Framebuffer fb;
	Framebuffer_Init(&fb);
	
	Demo_EyeDevil(&fb);*/
}
