
#include "keyanimation.h"

void KeyAnimation_Init(KeyAnimation* ka, const KeyList* keylist) {
	ka->currentkeyindex = 0;
	ka->nextkeyindex = 1;
	ka->durationcounter = 0;
	ka->keylist = keylist;
}

int16_t KeyAnimation_GetValue(const KeyAnimation* ka) {
	int16_t value;
	
	int16_t currentvalue = ka->keylist->key[ka->currentkeyindex].value;
	Key_Type currenttype = ka->keylist->key[ka->currentkeyindex].type;
	
	if ( currenttype == Linear ) {
		uint16_t currentduration = ka->keylist->key[ka->currentkeyindex].duration;
		int16_t nextvalue = ka->keylist->key[ka->nextkeyindex].value;
		value = currentvalue + (ka->durationcounter * (nextvalue - currentvalue)) / currentduration; 
	}
	else {
		value = currentvalue; 
	}
	return value;
}

KeyAnimation_Return KeyAnimation_Update(KeyAnimation* ka) {
	KeyAnimation_Return returnvalue = AnimationIsRunning;

	ka->durationcounter++;
	if ( ka->durationcounter == ka->keylist->key[ka->currentkeyindex].duration ) {
		ka->durationcounter = 0;
		
		ka->currentkeyindex++;
		if ( ka->currentkeyindex == ka->keylist->size ) {
			returnvalue = AnimationIsOver;
			ka->currentkeyindex = 0;
		}
			
		ka->nextkeyindex++;
		if ( ka->nextkeyindex == ka->keylist->size ) {
			ka->nextkeyindex = 0;
		}
	}
	
	return returnvalue;
}

