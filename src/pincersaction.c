#include "robot.h"
#include "pincers.h"
#include "pincersaction.h"
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <robotdriver/imudriver.h>
#include <pathfollower/pathfollower.h>
#include <stdlib.h>
#include <stdio.h>

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
	if(first) {
		first = 0;
		onOpenPincers(catchSecond);
		printf("Going to deliver first shell\n");
		ffollow("rocks2start", openPincers);
	} else {
		onOpenPincers(NULL);
		printf("Going to deliver second shell\n");
		ffollow("rocks2start2", openPincers);
	}
}

static void back(){
	setRobotDistance(0);
	queueSpeedChange(-0.15, NULL);
	queueStopAt(-50, deliver);
}

static void stopAndCatch(){
	setBlockingCallback(NULL);
	fastSpeedChange(0);
	enableHeadingControl(1);
	tryCapture();
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

static void reopen(){
	onOpenPincers(getShell);
	openPincers();
}

static void turn(){
	if(first){
		if(getTeam() == GREEN_TEAM)
			setTargetHeading(180 + getHeading(), getShell);
		else
			getShell();
	} else {
		setTargetHeading(180 + getHeading(), reopen);
	}
}

static void catchSecond() {
	finish();
	onClosePincers(turn);
	ffollow("start2rocks", closePincers);
}

void catchShells(){
	onTryCapture(back);
	onOpenPincers(turn);
	finish();
	ffollow("net2rocks", openPincers);
}
