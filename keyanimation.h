
#ifndef KEYANIMATION_H
#define KEYANIMATION_H

#include <stdint.h>
#include <stdio.h>

typedef enum Key_Type {
	Constant,
	Linear
}Key_Type;

typedef enum KeyAnimation_Return {
	AnimationIsRunning,
	AnimationIsOver
}KeyAnimation_Return;

typedef struct Key {
	int16_t value;
	uint16_t duration;
	Key_Type type;;
}Key;

typedef struct KeyList {
	uint16_t size;
	Key key[];
}KeyList;

typedef struct KeyAnimation {
	uint16_t currentkeyindex;
	uint16_t nextkeyindex;
	uint16_t durationcounter;
	const KeyList* keylist;
}KeyAnimation;

void KeyAnimation_Init(KeyAnimation* ka, const KeyList* keylist);
int16_t KeyAnimation_GetValue(const KeyAnimation* ka);
KeyAnimation_Return KeyAnimation_Update(KeyAnimation* ka);

#endif
