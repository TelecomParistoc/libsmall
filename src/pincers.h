#ifndef PINCERS_H
#define PINCERS_H

// Sets max torque for pincers, called in initRobot
void initPincersAx12();

// Functions to drive the Ax-12 for pincers
void onOpenPincers(void (*callback)(void));
void onTryCapture(void (*callback)(void));
void onClosePincers(void (*callback)(void));
void openPincers();
void tryCapture();
void closePincers();
void testCallback();

#endif
