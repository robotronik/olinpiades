
#include "eyedevil.h"
#include "eyedevil_sprites.h"
#include "sprite.h"

// describes an animation
const KeyList test_Eye_expression = {
4*6, // <--- Number of keyframes, don't forget to update it :)
{
// blink
// key value, key duration, interpolation (Constant, Linear)
{Closed,4,Linear},
{Closed,4,Linear},   // the value changes linearly from 'Closed' to 'Open' in 4 frames
{Open,200,Linear}, // the value changes linearly from 'Open' to 'Closed' in 10 frames
{Open,4,Linear},

// blink
{Closed,4,Linear},
{Closed,4,Linear},
{Open,50,Linear},
{Open,4,Linear},

//blink
{Closed,4,Linear},
{Closed,4,Linear},
{Open,300,Linear},
{Open,4,Linear},

// double_blink
{Closed,4,Linear},
{Closed,4,Linear},
{Open,4,Linear},
{Open,4,Linear},
//
{Closed,4,Linear},
{Closed,4,Linear},
{Open,500,Linear},
{Open,4,Linear},

//blink
{Closed,4,Linear},
{Closed,4,Linear},
{Open,40,Linear},
{Open,4,Linear},
}
};

const KeyList test_Eye_pupil_x = {
4, // <-- don't forget to update the number of frames !
{
{2,50,Linear},
{2,3,Linear},
{4,60,Linear},
{4,3,Linear},
}
};
const KeyList test_Eye_pupil_y = {
4, // <-- ... !
{
{0,70,Linear},
{0,3,Linear},
{2,90,Linear},
{2,3,Linear},
}
};


void Demo_EyeDevil(Framebuffer* fb) {	
	// create a devil eye, with the animations up here 
	Eye eye;
	Eye_Init(&eye, &test_Eye_expression, &test_Eye_pupil_x, &test_Eye_pupil_y);
	
	while (1) {
		//pause_us(40000); // wait some time between animated frames
		Eye_Update(&eye); // switch to the next next animation frame of the eye

		Framebuffer_Clear(fb); // clear image buffer

		Eye_Draw(&eye, fb); // draw the eye


		for (int i = 0; i < 16; i++)
		{
			write_column(i, fb->data[i]);
		}

	}
}




