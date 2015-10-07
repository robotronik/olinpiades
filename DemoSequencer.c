
#include "DemoSequencer.h"

// init demosequencer with a demosequence
void DemoSequencer_Init(DemoSequencer* this, const DemoSequence* demoSequence) {
	this->currentDemoIndex = 0;
	this->demoSequence = demoSequence;
	this->frameCounter = 0;
	this->sequencerIsEnabled = 1;
	
	// init the first demo
	DemoFrame demoFrame = this->demoSequence->demoFrame[0];
	(*demoFrame.demo.demoInit)();
} 

// update demo, and if finished switch to another. and loop the sequence at the end
void DemoSequencer_Update(DemoSequencer* this, Framebuffer* fb) {
	// Update the current demo
	DemoFrame demoFrame = this->demoSequence->demoFrame[this->currentDemoIndex];
	(*demoFrame.demo.demoUpdate)(fb);
	
	// check if the demo is over
	if ( this->sequencerIsEnabled ) {
	if ( this->frameCounter++ == demoFrame.numberOfFrames ) {
		this->frameCounter = 0;
		// quit demo
		(*demoFrame.demo.demoQuit)();
		// next demo
		if ( this->currentDemoIndex++ == this->demoSequence->size )
			this->currentDemoIndex = 0;
		// Init new demo
		demoFrame = this->demoSequence->demoFrame[this->currentDemoIndex];
		(*demoFrame.demo.demoInit)();
	}
	}
}

// Switch to another demoSequence
void DemoSequencer_ChangeDemoSequence(DemoSequencer* this, const DemoSequence* demoSequence) {
	// quit current demo
	DemoFrame demoFrame = this->demoSequence->demoFrame[this->currentDemoIndex];
	(*demoFrame.demo.demoQuit)();
	
	// reinit with the new demoSequence
	DemoSequencer_Init(this, demoSequence);

}

// Switch to another demo
void DemoSequencer_ChangeDemo(DemoSequencer* this, unsigned int demoIndex) {
	// quit current demo
	DemoFrame demoFrame = this->demoSequence->demoFrame[this->currentDemoIndex];
	(*demoFrame.demo.demoQuit)();
	
	// set current demo
	this->currentDemoIndex = demoIndex;
	
	// reset frameCounter
	this->frameCounter = 0;
	
	// init it
	demoFrame = this->demoSequence->demoFrame[this->currentDemoIndex];
	(*demoFrame.demo.demoInit)();
}

// Enable sequencer
void DemoSequencer_EnableAutoSwitch(DemoSequencer* this) {
	this->sequencerIsEnabled = 1;
}

// Stay on the same demo forever
void DemoSequencer_DisableAutoSwitch(DemoSequencer* this) {
	this->sequencerIsEnabled = 0;
}






