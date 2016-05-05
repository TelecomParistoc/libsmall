#include <librobot/robot.h>
#include <librobot/fish.h>
#include <librobot/pincers.h>
#include <librobot/pincersaction.h>
#include <pathfollower/pathfollower.h>
#include <robotdriver/toolboxdriver.h>
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <robotdriver/motordriver.h>
#include <stdlib.h>
#include <stdio.h>

static int started = 0;

static void onStart() {
	if(started == 1)
		started = 2;
}
static void quitAndRestart() {
    exit(-23);
}
static void onStop() {
    if(started == 2) {
        setLED(1, 0);
        setLED(2, 0);
        setLED(3, 0);
        scheduleIn(50, quitAndRestart);
    }
	started = 1;
    if(getMode() == TEST_MODE)
        exit(0);
}
static void checkCollisions() {
    static int lastStopped = 0;
    if(getTargetSpeed() >= 0){
        if(isRobotFront()) {
            lastStopped = 1;
            forceStop(1);
            setLED(3, 1);
        } else if(lastStopped) {
            lastStopped = 0;
            forceStop(0);
            setLED(3, 0);
        }
    }
    if(getTargetSpeed() <= 0) {
        if(isRobotBehind()) {
            lastStopped = 1;
            forceStop(1);
            setLED(3, 1);
        } else if(lastStopped) {
            lastStopped = 0;
            forceStop(0);
            setLED(3, 0);
        }
    }
}
static void nearNet() {
    releaseFish();
    printf("near net\n");
}
static void nearRocks() {
    faceShell();
}
static void nearRocksAgain() {
    openPincers();
}
static void nearFishes() {
    startFishing();
    printf("started fishes\n");
}
static void onEndOfTheGame() {
    forceStop(1);
	axReset();
	printf("game end\n");
    setRGB(0, 255, 255);
}

int main() {
    // init
    initRobot();
    enableHeadingControl(0);
    setCurrentLocation(196, 940);
    onGameStop(onStop);
    onGameStart(onStart);
    setLED(3, 0);
    setLED(2, 0);

    // wait for start
    while(started != 1) {
    	waitFor(200);
    	setLED(1, 0);
    	waitFor(200);
    	setLED(1, 1);
    }
    while(started != 2)
    	waitFor(200);

    // start
    setLED(2, 1);
    setLED(1, 0);
    setRobotHeading(90);
    setTargetHeading(0, NULL);
    setRobotDistance(0);
    enableHeadingControl(1);
    setActiveDetectors(all);
    scheduleIn(90000, onEndOfTheGame);

    // fishes
    fishStop();
    ffollow("start2water", nearFishes);
    while(!fishHasFinished()) {
        waitFor(50);
    	checkCollisions();
    }
    fishStop();
    ffollow("water2net", nearNet);
    while(!fishHasFinished()) {
        waitFor(50);
    	checkCollisions();
    }
    pincersStop();
    ffollow("net2rocks", nearRocks);
    while(!pincersHasFinished()) {
        waitFor(50);
    	checkCollisions();
    }
    pincersStop();
    ffollow("rocks2rocks", nearRocksAgain);
    while(!pincersHasFinished()) {
        waitFor(50);
    	checkCollisions();
    }
    ffollow("rocks2start", openPincers);
    while(1) {
        waitFor(50);
    	checkCollisions();
    }
    return 0;
}
