#include <robotdriver/toolboxdriver.h>
#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#include "pincers.h"

// Ax-12 stuff
#define PINCERSTORQUE 100

// Left Ax-12
#define AXLEFTPINCER 130
#define AXLEFTIN     557
#define AXLEFTOUT    338

// Right Ax-12
#define AXRIGHTPINCER 129
#define AXRIGHTIN     557
#define AXRIGHTOUT    338

static void (*openPincersCallback)(void) = NULL;
static void (*closePincersCallback)(void) = NULL;

void initPincersAx12() {
	axSetTorqueSpeed(AXLEFTPINCER , PINCERSTORQUE, -1, 0):
	axSetTorqueSpeed(AXRIGHTPINCER, PINCERSTORQUE, -1, 0):
}

void onOpenPincers(void (*callback)(void)) {
	openPincersCallback = callback;
}

void onClosePincers(void (*callback)(void)) {
	closePincersCallback = callback;
}

void openPincers() {
	axMove(AXLEFTPINCER , AXLEFTOUT , NULL);
	axMove(AXTIGHTPINCER, AXRIGHTOUT, openPincersCallback);
}

void closePincers() {
	axMove(AXLEFTPINCER , AXLEFTIN , NULL);
	axMove(AXTIGHTPINCER, AXRIGHTIN, closePincersCallback);
}

void testCallback() {
	int val = axHasFinishedMove();
	if(val == 1)
		printf("Pinces bien repliées\n");
	if(val == 2)
		printf("Objet attrapé\n");
}
