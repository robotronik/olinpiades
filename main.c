
#include <stdlib.h>
#include "eyedevil.h"
#include "anti_text.h"

void Demo_EyeDevil(Framebuffer* fb);

int main(void)
{
	//init_hardware();
	//write_SPI1(0x0FFF);
		// create and init a framebuffer : it holds the current picture 
	//that will be modified and then drawn to the screen
	Framebuffer fb;
	Framebuffer_Init(&fb);
	
	Demo_EyeDevil(&fb);
}

