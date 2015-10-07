#include <stdlib.h>
#include "eyedevil.h"
#include "anti_text.h"

void Demo_EyeDevil(Framebuffer* fb);

int main(void)
{
		// create and init a framebuffer : it holds the current picture 
	//that will be modified and then drawn to the screen
	Framebuffer fb;
	Framebuffer_Init(&fb);
	
	Text_DrawChar(&fb, 'U', 0, 0);
	
	Framebuffer_Draw(&fb);
	//Demo_EyeDevil(&fb);
}











