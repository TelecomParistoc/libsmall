#include "robot.h"
#include "fisharm.h"
#include "fish.h"
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <robotdriver/motordriver.h>
#include <robotdriver/toolboxdriver.h>
#include <pathfollower/pathfollower.h>
#include <stdlib.h>
#include <stdio.h>

static void fishstep();
static void fishstep2();
static void delay();

static int step = 0;
static int straight = 0;
static int finished = 0;
static int nbfish = 0;

static void (*endFishingCallback)(void) = NULL;

int fishHasFinished(){
	return finished;
}

void fishStop(){
	finished = 0;
}

static void finish(){
	finished = 1;
	printf("Fish action finished\n");
}

void delayStart(){
	finish();
}

static void leave(){
	armUp();
	finish();
}

static void end2(){
	onFishCapture(NULL);
	if(getTeam() == GREEN_TEAM){
		setCurrentLocation(816 + getRobotDistance(), 110);
		printf("Position en x : %f\n", 800 + getRobotDistance());
	} else {
		setCurrentLocation(816 - getRobotDistance(), 110);
		printf("Position en x : %f\n", 796 - getRobotDistance());
	}
	jumpTo(12);
	armUp();
	if(getTableConfig() == 4)
		setActiveDetectors(all);
	finish();
}

static void withFish2(){
	if(getTeam() == GREEN_TEAM) {
		setCurrentLocation(816 + getRobotDistance(), 110);
		printf("Position en x : %f\n", 816 + getRobotDistance());
	} else {
		setCurrentLocation(816 - getRobotDistance(), 110);
		printf("Position en x : %f\n", 816 - getRobotDistance());
	}
	printf("Pos de getPosition :  X = %f || Y = %f\n)", getCurrentX(), getCurrentY());
	finish();
}

static void stop2(){
	step = 0;
	clearMotionQueue();
	queueSpeedChange(0, NULL);
	onFishCapture(NULL);
	onArmMid(withFish2);
	armMid();
}

static void fish2(){
	printf("Let's get some fish 2\n");
	setRobotDistance(0);
	onFishCapture(stop2);
	if(hasFish()){
		onFishCapture(NULL);
		stop2();
		return;
	}
	if(getTeam() == GREEN_TEAM) {
		queueSpeedChange(-(0.10 - 0.02 * nbfish), NULL);
		queueStopAt(-400, end2);
	} else {
		queueSpeedChange(0.10 - 0.02 * nbfish, NULL);
		queueStopAt(400, end2);
	}
}

static void schedulestep2(){
	scheduleIn(2000, fishstep2);
}

static void fishstep2(){
	printf("Let's get some fish step2\n");
	if(getTeam() == GREEN_TEAM)
		setRobotDistance(-100 * step);
	else
		setRobotDistance(100 * step);
	onFishCapture(stop2);
	if(step < 4) {
		step ++;
		if(getTeam() == GREEN_TEAM) {
			queueSpeedChange(-0.05, NULL);
			queueStopAt(-100 * step, schedulestep2);
		} else {
			queueSpeedChange(0.05, NULL);
			queueStopAt(100 * step, schedulestep2);
		}
	} else {
		setCurrentLocation(800 + getRobotDistance(), 114);
		armUp();
	}
}

void turn2(){
	printf("On va dans l'autre sens\n");
	if(getTeam() == GREEN_TEAM)
		setTargetHeading(0, armDown);
	else
		setTargetHeading(180, armDown);
}

static void end(){
	onFishCapture(NULL);
	if(getTeam() == GREEN_TEAM){
		setCurrentLocation(391 + getRobotDistance(), 111);
		printf("Position en x : %f\n", 391 + getRobotDistance());
	} else {
		setCurrentLocation(391 - getRobotDistance(), 111);
		printf("Position en x : %f\n", 391 - getRobotDistance());
	}
	onArmMid(finish);
	armMid();
}

void releaseFish(){
	nbfish ++;
	onMagnetOff(drop);
	onArmMid(magnetOn);
	if(nbfish == 4){
		onMagnetOn(leave);
		if(getTableConfig() == 4)
			setActiveDetectors(all);
	} else {
		jumpTo(8);
		onMagnetOn(finish);
	}
	setCurrentLocation(getCurrentX(), getCurrentY());
	magnetOff();
}

static void withFish(){
	if(getTeam() == GREEN_TEAM){
		setCurrentLocation(412 + getRobotDistance(), 111);
		printf("Position en x : %f\n", 391 + getRobotDistance());
	} else {
		setCurrentLocation(412 - getRobotDistance(), 111);
		printf("Position en x : %f\n", 391 - getRobotDistance());
	}
	printf("Position du getPosition X = %f || Y = %f\n", getCurrentX(), getCurrentY());
	finish();
}

static void stop(){
	clearMotionQueue();
	queueSpeedChange(0, NULL);
	onFishCapture(NULL);
	onArmMid(withFish);
	armMid();
}

static void falseAlert(){
	onFishCapture(delay);
}

static void check(){
	if (hasFish())
		stop();
	else
		falseAlert();
}

static void delay(){
	onFishCapture(NULL);
	scheduleIn(100, check);
}


static void fish(){
	setActiveDetectors(right);
	printf("Let's get some fish\n");
	setRobotDistance(0);
	onArmDown(fish2);
	onArmMid(withFish);
	//onFishCapture(delay);
	if(getTeam() == GREEN_TEAM){
		queueSpeedChange(0.05, NULL);
		queueStopAt(400, armMid);
	} else {
		queueSpeedChange(-0.05, NULL);
		queueStopAt(-400, armMid);
	}
}

static void schedulestep(){
	scheduleIn(2000, fishstep);
}

static void fishstep(){
	printf("Let's get some fish step\n");
	onArmDown(fishstep2);
	if(getTeam() == GREEN_TEAM)
		setRobotDistance(100 * step);
	else
		setRobotDistance(-100 * step);
	onFishCapture(stop);
	if(step < 4) {
		step ++;
		if(getTeam() == GREEN_TEAM){
			queueSpeedChange(0.05, NULL);
			queueStopAt(100 * step, schedulestep);
		} else {
			queueSpeedChange(-0.05, NULL);
			queueStopAt(-100 * step, schedulestep);
		}
	} else {
		armUp();
	}
}

void startFishing(){
	setActiveDetectors(none);
	straight = 1;
	onFishCapture(NULL);
	if (straight)
		onArmDown(fish);
	else
		onArmDown(fishstep);
	if(getTeam() == GREEN_TEAM)
		setTargetHeading(0, armDown);
	else
		setTargetHeading(180, armDown);
}

void startFishingStep(){
	onFishCapture(NULL);
	onArmUp(endFishingCallback);
	onArmDown(fish);
	if(getTeam() == GREEN_TEAM)
		setTargetHeading(0, armDown);
	else
		setTargetHeading(180, armDown);
}

void pauseFish(){
	printf("PAUSE\n");
	clearMotionQueue();
	queueSpeedChange(0, NULL);
}

void resumeFish(){
	if(!hasFish()){
		if(!nbfish){
			if(getTeam() == GREEN_TEAM) {
				queueSpeedChange(0.10 - 0.02 * nbfish, NULL);
				queueStopAt(400, end);
			} else {
				queueSpeedChange(-(0.10 - 0.02 * nbfish), NULL);
				queueStopAt(-400, end);
			}
		} else {
			if(getTeam() == GREEN_TEAM) {
				queueSpeedChange(-(0.10 - 0.02 * nbfish), NULL);
				queueStopAt(-400, end2);
			} else {
				queueSpeedChange(0.10 - 0.02 * nbfish, NULL);
				queueStopAt(400, end2);
			}
		}
	}
}

void onEndFishing(void (*callback)(void)){
	endFishingCallback = callback;
}
