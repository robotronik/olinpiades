
#include "eyedevil.h"


void Eye_Init(Eye* this,	const KeyList* keyListEyeState,  
													const KeyList* keyListPupil_x, 
													const KeyList* keyListPupil_y) {
													
	KeyAnimation_Init(&this->kaEyeState, keyListEyeState);
	KeyAnimation_Init(&this->kaEyePupil_x, keyListPupil_x);
	KeyAnimation_Init(&this->kaEyePupil_y, keyListPupil_y);
}

void Eye_Update(Eye* this) {
	// next frame for each animations
	KeyAnimation_Update(&this->kaEyeState);
	KeyAnimation_Update(&this->kaEyePupil_x);
	KeyAnimation_Update(&this->kaEyePupil_y);
}

void Eye_Draw(const Eye* this, Framebuffer* fb) {
	
	// get animated values at the current frame
	Eye_State eyestate = KeyAnimation_GetValue(&this->kaEyeState);
	int16_t x = KeyAnimation_GetValue(&this->kaEyePupil_x);
	int16_t y = KeyAnimation_GetValue(&this->kaEyePupil_y);
	
	// else, draw the eye expression
	// choose sprite/clipping pair 
	const Sprite* eye_sprite = 0;
	const Framebuffer* eye_clip = 0;
	switch(eyestate) {
	case(Closed):
		eye_sprite = &eye_0;
		eye_clip = &eye_0_clip;
		break;
	case(HalfClosed):
		eye_sprite = &eye_1;
		eye_clip = &eye_1_clip;
		break;
	case(HalfOpen):
		eye_sprite = &eye_2;
		eye_clip = &eye_2_clip;
		break;
	case(Open):
		eye_sprite = &eye_3;
		eye_clip = &eye_3_clip;
		break;
	}
	
	Sprite_Draw(fb, eye_sprite, 0, 0);
	Sprite_DrawWithClipping(fb, eye_clip, &eye_pupil, x, y);
}





