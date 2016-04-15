#include <robotdriver/toolboxdriver.h>
#include <pathfollower/pathfollower.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "robot.h"
#include "pincers.h"

#define RAYON 453

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

void setPosInCorner(double angle){
	double x = -RAYON*cos(angle*M_PI/180);
	double y = -RAYON*sin(angle*M_PI/180);
	printf("Angle : %f\n", angle);
	printf("Trigo : X = %f || Y = %f\n", x, y);
	setCurrentLocation(x, y);
}

void initPincersAx12() {
	axSetTorqueSpeed(AXLEFTPINCER , 1023, -1, 0);
	axSetTorqueSpeed(AXRIGHTPINCER, 1023, -1, 0);
}

void refrainPincersAx12() {
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
	axMove(AXLEFTPINCER , AXLEFTOUT , openPincersCallback, 2000);
}

void openPincers() {
	initPincersAx12();
	axMove(AXRIGHTPINCER, AXRIGHTOUT, openLeft, 500);
}

void tryCapture() {
	refrainPincersAx12();
	axMove(AXLEFTPINCER , AXLEFTCAPTURE , NULL, 1000);
	axMove(AXRIGHTPINCER, AXRIGHTCAPTURE, tryCaptureCallback, 2000);
}

static void closeRight() {
	initPincersAx12();
	axMove(AXRIGHTPINCER, AXRIGHTIN, closePincersCallback, 2000);
}

void closePincers() {
	axMove(AXLEFTPINCER, AXLEFTIN, closeRight, 500);
}

void testCallback() {
	int val = axHasFinishedMove();
	if(val == 1)
		printf("Pinces bien repliées\n");
	if(val == 2)
		printf("Objet attrapé\n");
}
