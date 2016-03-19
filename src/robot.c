#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <robotdriver/motordriver.h>
#include <robotdriver/toolboxdriver.h>
#include <stdlib.h>
#include "robot.h"

void fishSensorManager();

static void (*gameStartCallback)(void) = NULL;
static void (*collisionDetectCallback)(int) = NULL;
static void (*collisionEndCallback)(int) = NULL;
static int collisions[3] = {0, 0, 0};

static void collisionsCallback() {
    for(int i=0; i<3; i++) {
        if(collisionDetectCallback != NULL && getCollisionDetector(i+3) && (!collisions[i])) {
            collisionDetectCallback(i);
        }
        if(collisionEndCallback != NULL && (!getCollisionDetector(i+3)) && collisions[i]) {
            collisionEndCallback(i);
        }
        collisions[i]= getCollisionDetector(i+3);
    }
}
static void sensorsCallback() {
    fishSensorManager();
    if(gameStartCallback != NULL && getSensor(1))
        gameStartCallback();
}

void initRobot() {
	initMotionController();
	initToolboxDriver();

	setRobotDistance(0);
	setRobotHeading(0);
	axReset();

	enableSensorCallback(1);
	disableSensorCallback(2);
	disableSensorCallback(3);
	disableSensorCallback(4);
	disableSensorCallback(5);
	setSensorsCallback(sensorsCallback);

	disableCollisionCallback(1);
	disableCollisionCallback(2);
	enableCollisionCallback(3);
	enableCollisionCallback(4);
	enableCollisionCallback(5);
	setCollisionsCallback(collisionsCallback);

	for(int i = 1 ; i < 5 ; i ++)
		setPWM(i, 255);
}

void onGameStart(void (*callback)(void)) {
    enableSensorCallback(1);
    gameStartCallback = callback;
}

void onCollisionDetect(void (*callback)(int)) {
    collisionDetectCallback = callback;
}
void onCollisionEnd(void (*callback)(int)) {
    collisionEndCallback = callback;
}

int getTableConfig() {
    return getButton(1) + getButton(2)*2 + getButton(3)*3;
}

void setRGB(char red, char green, char blue){
	setPWM(1, 255 - blue);
	setPWM(2, 255 - green);
	setPWM(3, 255 - red);
}
