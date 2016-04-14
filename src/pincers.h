#ifndef PINCERS_H
#define PINCERS_H

// Sets max torque for pincers, called in initRobot
void initPincersAx12();

// Functions to drive the Ax-12 for pincers
onOpenPincers(void (*callback)(void));
onTryCapture(void (*callback)(void));
onClosePincers(void (*callback)(void));
openPincers();
tryCapture();
closePincers();
testCallback();

#endif
