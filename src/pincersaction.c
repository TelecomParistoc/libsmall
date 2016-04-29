#include "robot.h"
#include "pincers.h"
#include "pincersaction.h"
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <robotdriver/imudriver.h>
#include <pathfollower/pathfollower.h>
#include <stdlib.h>

static void stopAndCatch();

static int first = 1;

static void getSecond(){
	setBlockingCallback(stopAndCatch);
	enableHeadingControl(0);
	queueSpeedChange(0.15, NULL);
}

static void catchSecond() {
	ffollow("start2rocks", getSecond);
}

static void deliver(){
	setCurrentLocation(getHeading());
	if(first) {
		if(getTableConfig() != 4)
			onOpenPincers(catchSecond);
		else
			onOpenPincers(closePincers);
		first = 0;
		ffollow("rocks2start", openPincers);
	} else {
		onOpenPincers(closePincers);
		ffollow("rocks2start2", openPincers);
	}
}

static void back(){
	setRobotDistance(0);
	queueSpeedChange(-0.15, NULL);
	queueStopAt(-100, deliver);
}


static void getFirst(){
	enableHeadingControl(0);
	queueSpeedChange(0.15, NULL);
}

static void stopAndCatch(){
	fastSpeedChange(0);
	enableHeadingControl(1);
	tryCapture();
}

void catchShells(){
	onTryCapture(back);
	setBlockingCallback(stopAndCatch);
	onOpenPincers(getFirst);
	ffollow("water2rocks", openPincers);
}
