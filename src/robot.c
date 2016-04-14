#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <robotdriver/motordriver.h>
#include <robotdriver/toolboxdriver.h>
#include <stdlib.h>
#include <stdio.h>
#include "robot.h"
#include "fisharm.h"
#include "pincers.h"

void fishSensorManager();

static void (*gameStartCallback)(void) = NULL;
static void (*gameStopCallback)(void) = NULL;
static void (*collisionDetectCallback)(int) = NULL;
static void (*collisionEndCallback)(int) = NULL;
static int collisions[3] = {0, 0, 0};
static int lastJack = 0;
static collisionConfig_t collConfig = all;

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
    if(gameStartCallback != NULL && getSensor(1) && !lastJack) {
        gameStartCallback();
        lastJack = 1;
    } else if(gameStopCallback != NULL && !getSensor(1) && lastJack){
        gameStopCallback();
        lastJack = 0;
    }
}

void initRobot() {
	initMotionController();
	initToolboxDriver();

	setRobotDistance(0);
	setRobotHeading(0);
	setRobotLocation(41, 1003);
	axReset();
	setRotationDirection(getTeam() == PURPLE_TEAM);

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

	initFishAx12();
	initPincersAx12();
	//setMoveStartCallback(updateAngleStartingMove);
	//setMoveEndCallback(updatePositionEndingMove);

    lastJack = getSensor(1);
}

void onGameStart(void (*callback)(void)) {
    enableSensorCallback(1);
    gameStartCallback = callback;
}
void onGameStop(void (*callback)(void)) {
    enableSensorCallback(1);
    gameStopCallback = callback;
}

void onCollisionDetect(void (*callback)(int)) {
    collisionDetectCallback = callback;
}
void onCollisionEnd(void (*callback)(int)) {
    collisionEndCallback = callback;
}
void setActiveDetectors(collisionConfig_t config) {
    collConfig = config;
}

int isRobotFront() {
    printf("check front (positive speed) %d %d %d\n",collisions[0],collisions[1],collisions[2]);
    switch (collConfig) {
        case all:
        case front:
            return collisions[FRONT_RIGHT_COLLISION] || collisions[FRONT_LEFT_COLLISION];
        case left:
            return collisions[FRONT_LEFT_COLLISION];
        case right:
            return collisions[FRONT_RIGHT_COLLISION];
        case rear:
        case none:
            return 0;
    }
    return 0;
}

int isRobotBehind() {
    //printf("check behind (negative speed) %d %d %d\n",collisions[0],collisions[1],collisions[2]);
    if(collConfig == all || collConfig == rear || collConfig == left || collConfig == right)
        return collisions[REAR_COLLISION];
    else
        return 0;
}


int getTableConfig() {
    return getButton(1) + getButton(2)*2 + getButton(3)*3;
}

void setRGB(char red, char green, char blue){
	setPWM(1, 255 - blue);
	setPWM(2, 255 - green);
	setPWM(3, 255 - red);
}

// roof top buttons
int getTeam() {
    return getButton(5);
}
int getMode() {
    return getButton(4);
}
