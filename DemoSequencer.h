#ifndef DEMOSEQUENCER_H
#define DEMOSEQUENCER_H

#include "framebuffer.h"

// a demo must provide those callbacks
typedef struct Demo {
	void (*demoInit)();
	void (*demoUpdate)(Framebuffer* fb);
	void (*demoQuit)();
}Demo;

// a demosequence frame
typedef struct DemoFrame {
	uint16_t numberOfFrames;
	Demo demo;
}DemoFrame;

// the demosequence to create
typedef struct DemoSequence {
	uint16_t size;
	DemoFrame demoFrame[];
}DemoSequence;

typedef struct DemoSequencer {
	uint16_t currentDemoIndex;
	const DemoSequence* demoSequence;
	uint16_t frameCounter;
	uint16_t sequencerIsEnabled;
}DemoSequencer;

// init demosequencer with a demosequence
void DemoSequencer_Init(DemoSequencer* this,const DemoSequence* demoSequence);
// update demo, and if finished switch to another. and loop the sequence at the end
void DemoSequencer_Update(DemoSequencer* this, Framebuffer* fb);
// Switch to another demoSequence
void DemoSequencer_ChangeDemoSequence(DemoSequencer* this, const DemoSequence* demoSequence);
// Switch to another demo
void DemoSequencer_ChangeDemo(DemoSequencer* this, unsigned int demoIndex);
// Enable sequencer
void DemoSequencer_EnableAutoSwitch(DemoSequencer* this);
// Stay on the same demo forever
void DemoSequencer_DisableAutoSwitch(DemoSequencer* this);

#endif


