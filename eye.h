#ifndef EYE_H
#define EYE_H

#include "framebuffer.h"
#include "sprite.h"
#include "keyanimation.h"
#include "eye_sprites.h"

typedef enum Eye_Type {
	Normal, Open = Normal,
	Upset,
	Happy,
	Closed
}Eye_Type;

typedef struct Eye {
	KeyAnimation kaEyeType;
	KeyAnimation kaEyeBlink;
	KeyAnimation kaEyePupil_x,kaEyePupil_y;
}Eye;

void Eye_Init(Eye* this,	const KeyList* keyListEyeType,
													const KeyList* keyListEyeBlink, 
													const KeyList* keyListPupil_x, 
													const KeyList* keyListPupil_y);
void Eye_Update(Eye* this);
void Eye_Draw(const Eye* this, Framebuffer* fb);

#endif
