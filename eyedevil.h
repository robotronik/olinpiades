#ifndef EYE_H
#define EYE_H

#include "framebuffer.h"
#include "sprite.h"
#include "keyanimation.h"
#include "eyedevil_sprites.h"

typedef enum Eye_State {
	Closed,
	HalfClosed,
	HalfOpen,
	Open
}Eye_State;

typedef struct Eye {
	KeyAnimation kaEyeState;
	KeyAnimation kaEyePupil_x,kaEyePupil_y;
}Eye;

// Init the eye with some animations (how much the eye is opened, pupil position )
void Eye_Init(Eye* this,	const KeyList* keyListEyeState,
	const KeyList* keyListPupil_x, 
	const KeyList* keyListPupil_y);
	
// Next animation frame
void Eye_Update(Eye* this);

// Draw the eye on a framebuffer
void Eye_Draw(const Eye* this, Framebuffer* fb);

#endif
