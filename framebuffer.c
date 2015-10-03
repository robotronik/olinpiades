
#include "framebuffer.h"

void Framebuffer_Init(Framebuffer* fb) {
	Framebuffer_Clear(fb);
}

void Framebuffer_Draw(Framebuffer* fb) {
	for(int y=0; y<FB_WIDTH_SHORT; y++) {
		select_column(y);
		print_column(fb->data[y]);
	}
}

void Framebuffer_Draw_Compatibility(Framebuffer* fb) {
	printf("\033[2J\033[1;1H");
	for(int y=0; y<FB_WIDTH_SHORT; y++) {
		for(int x=0; x<16; x++) {
			if ( fb->data[y] & ( 1 << (16-x) ) )
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
