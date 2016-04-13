#include <robotdriver/toolboxdriver.h>
#include <pathfollower/pathfollower.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "robot.h"
#include "pincers.h"

#define RAYON 100

// Ax-12 stuff
#define PINCERSTORQUE 300

// Left Ax-12
#define AXLEFTPINCER  130
#define AXLEFTIN      698
#define AXLEFTCAPTURE 425
#define AXLEFTOUT     300

// Right Ax-12
#define AXRIGHTPINCER  129
#define AXRIGHTIN      362
#define AXRIGHTCAPTURE 600
#define AXRIGHTOUT     730

static void (*openPincersCallback)(void) = NULL;
static void (*tryCaptureCallback)(void) = NULL;
static void (*closePincersCallback)(void) = NULL;

struct robotPoint getPosInCorner(double angle){
	struct robotPoint pos;
	pos.x = -RAYON*sin(angle*M_PI/180);
	pos.y = -RAYON*cos(angle*M_PI/180);
	return pos;
}

void initPincersAx12() {
	axSetTorqueSpeed(AXLEFTPINCER , PINCERSTORQUE, -1, 0);
	axSetTorqueSpeed(AXRIGHTPINCER, PINCERSTORQUE, -1, 0);
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

static void openLeft() {
	axMove(AXLEFTPINCER , AXLEFTOUT , openPincersCallback);
}

void openPincers() {
	axMove(AXRIGHTPINCER, AXRIGHTOUT, openLeft);
}

void tryCapture() {
	axMove(AXLEFTPINCER , AXLEFTCAPTURE , NULL);
	axMove(AXRIGHTPINCER, AXRIGHTCAPTURE, tryCaptureCallback);
}

static void closeRight() {
	axMove(AXRIGHTPINCER, AXRIGHTIN, closePincersCallback);
}

void closePincers() {
	axMove(AXLEFTPINCER, AXLEFTIN, closeRight);
}

void testCallback() {
	int val = axHasFinishedMove();
	if(val == 1)
		printf("Pinces bien repliées\n");
	if(val == 2)
		printf("Objet attrapé\n");
}
