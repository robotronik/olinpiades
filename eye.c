
#include "eye.h"

void Eye_Init(Eye* this,	const KeyList* keyListEyeType, 
													const KeyList* keyListEyeBlink, 
													const KeyList* keyListPupil_x, 
													const KeyList* keyListPupil_y) {
													
	KeyAnimation_Init(&this->kaEyeType, keyListEyeType);
	KeyAnimation_Init(&this->kaEyeBlink, keyListEyeBlink);
	KeyAnimation_Init(&this->kaEyePupil_x, keyListPupil_x);
	KeyAnimation_Init(&this->kaEyePupil_y, keyListPupil_y);
}

void Eye_Update(Eye* this) {
	KeyAnimation_Update(&this->kaEyeType);
	KeyAnimation_Update(&this->kaEyeBlink);
	KeyAnimation_Update(&this->kaEyePupil_x);
	KeyAnimation_Update(&this->kaEyePupil_y);
}

void Eye_Draw(const Eye* this, Framebuffer* fb) {
	
	Eye_Type expression = KeyAnimation_GetValue(&this->kaEyeType);
	Eye_Type eyeGlobalState = KeyAnimation_GetValue(&this->kaEyeBlink);
	
	// blink ? eyes don't need to blink when closed (happy)
	if ( eyeGlobalState == Closed && expression != Happy ) {
		Sprite_Draw(fb, &eye_closed, 0, 7);
		return;
	}
	
	// else, draw the eye expression
	switch(expression) {
	case(Normal):
		Sprite_Draw(fb, &eye_normal, 0, 1);
		break;
	case(Upset):
		Sprite_Draw(fb, &eye_upset, 0, 3);
		break;
	case(Happy):
		Sprite_Draw(fb, &eye_happy, 0, 1);
		break;
	case(Closed):
		Sprite_Draw(fb, &eye_closed, 0, 7);
		break;
	}
	
	//draw the pupil, only for some expressions
	if ( expression == Normal || expression == Upset ) {
		int16_t x = KeyAnimation_GetValue(&this->kaEyePupil_x);
		int16_t y = KeyAnimation_GetValue(&this->kaEyePupil_y);
		Sprite_Draw(fb, &eye_pupil, x, y);
	}
}





