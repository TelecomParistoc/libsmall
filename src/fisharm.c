#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <robotdriver/motordriver.h>
#include <robotdriver/toolboxdriver.h>
#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#include "fisharm.h"

// Ax-12 that controls the arm

#define AXFISHARM 121
#define UP        790
#define MID       600
#define DOWN      480
#define ARMSPEED  400

// Ax-12 that controls the magnet

#define AXMAGNETCONTROL 124
#define ON              520
#define OFF             280
#define MAGNETSPEED     400

static void (*captureCallback)(void) = NULL;
static void (*releaseCallback)(void) = NULL;
static void (*magnetOnCallback)(void) = NULL;
static void (*magnetOffCallback)(void) = NULL;
static void (*armUpCallback)(void) = NULL;
static void (*armMidCallback)(void) = NULL;
static void (*armDownCallback)(void) = NULL;

int hasFish() {
	return getSensor(2);
}

void fishSensorManager() {
	if(hasFish()) {
		if(captureCallback != NULL)
			captureCallback();
	} else {
		if(releaseCallback != NULL)
			releaseCallback();
	}
}

void onFishCapture(void (*callback)(void)) {
	enableSensorCallback(2);
	captureCallback = callback;
}

void onFishRelease(void (*callback)(void)) {
	enableSensorCallback(2);
	releaseCallback = callback;
}

void onMagnetOn(void (*callback)(void)) {
	magnetOnCallback = callback;
}

void onMagnetOff(void (*callback)(void)) {
	magnetOffCallback = callback;
}

void onArmUp(void (*callback)(void)) {
	armUpCallback = callback;
}

void onArmMid(void (*callback)(void)) {
	armMidCallback = callback;
}

void onArmDown(void (*callback)(void)) {
	armDownCallback = callback;
	printf("Changing arm down callback\n");
}

void waitForFish() {
	onFishCapture(armMid);
	printf("Waiting for a fish\n");
}

void initFishAx12() {
	axSetTorqueSpeed(AXMAGNETCONTROL, -1, MAGNETSPEED, 0);
	axSetTorqueSpeed(AXFISHARM      , -1, ARMSPEED   , 0);
}

void magnetOn() {
	setRGB(0, 0, 0);
	axMove(AXMAGNETCONTROL, ON, magnetOnCallback, 2000);
}

void magnetOff() {
	axMove(AXMAGNETCONTROL, OFF, magnetOffCallback, 2000);
}

void armUp() {
	axMove(AXFISHARM, UP, armUpCallback, 1000);
}

void armMid() {
	onFishCapture(NULL);
	setRGB(0, 0, 255);
	axMove(AXFISHARM, MID, armMidCallback, 1000);
}

void armDown() {
	axMove(AXFISHARM, DOWN, armDownCallback, 1000);
	exit(0);
}

void drop(){
	axMove(AXFISHARM, MID - 20, armMid, 1000);
}
