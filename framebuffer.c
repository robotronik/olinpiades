
#include "framebuffer.h"

void Framebuffer_Init(Framebuffer* fb) {
	Framebuffer_Clear(fb);
}

// draw call that comply with hardware abstraction
void Framebuffer_Draw(const Framebuffer* fb) {
	#if ARCH == PC
	Framebuffer_Draw_Compatibility(fb);
	#else
	for(int y=0; y<FB_WIDTH_SHORT; y++) {
		select_column(y);
		print_column(fb->data[y]);
	}
	#endif
}

// draw call for PC, so that everything drawn isn't rotated by 90°
void Framebuffer_Draw_Compatibility(const Framebuffer* fb) {
	printf("\033[2J\033[1;1H");
	for(int y=0; y<FB_WIDTH_SHORT; y++) {
		for(int x=0; x<16; x++) {
			if ( fb->data[y] & ( 1 << (15-x) ) )
				printf("o ");
			else
				printf("- ");
		}
		printf("\n");
	}
}

void Framebuffer_Clear(Framebuffer* fb) {
		for(int y=0; y<FB_WIDTH_SHORT; y++) 
			fb->data[y] = 0;
}
