#include <robotdriver/toolboxdriver.h>
#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#include "pincers.h"

// Ax-12 stuff
#define PINCERSTORQUE 100

// Left Ax-12
#define AXLEFTPINCER  130
#define AXLEFTIN      698
#define AXLEFTCAPTURE 340
#define AXLEFTOUT     235

// Right Ax-12
#define AXRIGHTPINCER  129
#define AXRIGHTIN      362
#define AXRIGHTCAPTURE 610
#define AXRIGHTOUT     798

static void (*openPincersCallback)(void) = NULL;
static void (*tryCaptureCallback)(void) = NULL;
static void (*closePincersCallback)(void) = NULL;

void initPincersAx12() {
	axSetTorqueSpeed(AXLEFTPINCER , PINCERSTORQUE, -1, 0):
	axSetTorqueSpeed(AXRIGHTPINCER, PINCERSTORQUE, -1, 0):
}

void onOpenPincers(void (*callback)(void)) {
	openPincersCallback = callback;
}

void onTryCapture(void (*callback)(void)) {
	tryCaptureCallback = callback;
}

void onClosePincers(void (*callback)(void)) {
	closePincersCallback = callback;
}

static void openRight() {
	axMove(AXRIGHTPINCER, AXRIGHTOUT, openPincersCallback);
}

void openPincers() {
	axMove(AXLEFTPINCER , AXLEFTOUT , openRight);
}

void tryCapture() {
	axMove(AXLEFTPINCER , AXLEFTCAPTURE , NULL);
	axMove(AXRIGHTPINCER, AXRIGHTCAPTURE, tryCaptureCallback);
}

static void closeLeft() {
	axMove(AXLEFTPINCER, AXLEFTIN, closePincersCallback);
}

void closePincers() {
	axMove(AXRIGHTPINCER, AXRIGHTIN, closeLeft);
}

void testCallback() {
	int val = axHasFinishedMove();
	if(val == 1)
		printf("Pinces bien repliées\n");
	if(val == 2)
		printf("Objet attrapé\n");
}
