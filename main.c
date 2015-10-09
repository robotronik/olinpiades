
#include <stdlib.h>
#include "eyedevil.h"
#include "anti_text.h"

void Demo_EyeDevil(Framebuffer* fb);

int main(void)
{
	Framebuffer fb;
	Framebuffer_Init(&fb);
	
	Demo_EyeDevil(&fb);
}

