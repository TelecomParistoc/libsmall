#include "robot.h"
#include "pincers.h"
#include "pincersaction.h"
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <robotdriver/imudriver.h>
#include <pathfollower/pathfollower.h>
#include <stdlib.h>

static void catchSecond();

static int first = 1;
static int finished = 0;

int pincersHasFinished(){
	return finished;
}

void pincersStop(){
	finished = 0;
}

static void finish(){
	finished = 1;
}

static void deliver(){
	setPosInCorner(getHeading());
	onOpenPincers(closePincers);
	if(first) {
		first = 0;
		ffollow("rocks2start", openPincers);
	} else {
		ffollow("rocks2start2", openPincers);
	}
}

static void back(){
	setRobotDistance(0);
	queueSpeedChange(-0.15, NULL);
	queueStopAt(-100, deliver);
}


static void getShell(){
	if(getTableConfig() != 4){
		setBlockingCallback(stopAndCatch);
		enableHeadingControl(0);
		queueSpeedChange(0.15, NULL);
	}
	else{
		ffollow("rocks2start", closePincers);
	}
}

static void stopAndCatch(){
	fastSpeedChange(0);
	enableHeadingControl(1);
	tryCapture();
}

static void catchSecond() {
	ffollow("start2rocks", getShell);
}

void catchShells(){
	onTryCapture(back);
	onOpenPincers(getShell);
	finish();
	ffollow("water2rocks", openPincers);
}
