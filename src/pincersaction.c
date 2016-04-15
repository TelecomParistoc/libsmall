#include "robot.h"
#include "pincers.h"
#include "pincersaction.h"
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <robotdriver/imudriver.h>
#include <stdlib.h>
#include <stdio.h>

static void turn();

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
	if(first)
		first = 0;
	onOpenPincers(finish);
	onClosePincers(turn);
	finish();
}

static void back(){
	setRobotDistance(0);
	queueSpeedChange(-0.15, NULL);
	queueStopAt(-70, deliver);
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
		onOpenPincers(finish);
		onClosePincers(turn);
		finish();
	}
}

static void reopen(){
	onOpenPincers(getShell);
	openPincers();
}

static void turn(){
	if(first){
		onOpenPincers(getShell);
		setTargetHeading(200, openPincers);
	} else {
		setTargetHeading(180 + getHeading(), reopen);
	}
}

void catchShells(){
	onTryCapture(back);
	turn();
}
