#include <librobot/robot.h>
#include <librobot/fisharm.h>
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <robotdriver/motordriver.h>
#include <robotdriver/toolboxdriver.h>
#include <pathfollower/pathfollower.h>
#include <stdlib.h>
#include <stdio.h>

static void releaseFish();

static int nbFish = 0;
static int step = 0;
static int straight = 0;

static void (*endFishingCallback)(void) = NULL;

static void caca() {
	printf("lol\n");
}

static void withFish2(){
	if(getTeam() == GREEN_TEAM) {
		setCurrentLocation(800 + getRobotDistance(), 114);
		printf("Position en x : %f\n", 800 + getRobotDistance());
	} else {
		setCurrentLocation(800 - getRobotDistance(), 114);
		printf("Position en x : %f\n", 800 - getRobotDistance());
	}
	printf("Pos de getPosition :  X = %f || Y = %f\n)", getCurrentX(), getCurrentY());
	ffollow("water2net", releaseFish);
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
	printf("Let's get some fish\n");
	setRobotDistance(0);
	onFishCapture(stop2);
	if(getTeam() == GREEN_TEAM) {
		queueSpeedChange(-0.05, caca);
		queueStopAt(-400, caca);
	} else {
		queueSpeedChange(0.05, caca);
		queueStopAt(400, caca);
	}
}

static void schedulestep2(){
	scheduleIn(2000, fishstep2);
}

static void fishstep2(){
	printf("Let's get some fish\n");
	if(getTeam() == GREEN_TEAM)
		setRobotDistance(-100 * step);
	else
		setRobotDistance(100 * step);
	onFishCapture(stop2);
	if(step < 4) {
		step ++;
		if(getTeam() == GREEN_TEAM) {
			queueSpeedChange(-0.05, caca);
			queueStopAt(-100 * step, schedulestep2);
		} else {
			queueSpeedChange(0.05, caca);
			queueStopAt(100 * step, schedulestep2);
		}
	} else {
		setCurrentLocation(800 + getRobotDistance(), 114);
		armUp();
	}
}

static void turn2(){
	if (straight)
		onArmDown(fish2);
	else
		onArmDown(fishstep2);
	if(getTeam == GREEN_TEAM)
		setTargetHeading(0, armDown);
	else
		setTargetHeading(180, armDown);
}

static void next(){
	if(nbFish < 4)
		ffollow("net2water", turn2);
	else {
		if(getTeam() == GREEN_TEAM)
			setCurrentLocation(391 + getRobotDistance(), 111);
		else
			setCurrentLocation(391 - getRobotDistance(), 111);
		armUp();
	}
}

static void releaseFish(){
	onMagnetOff(drop);
	onArmMid(magnetOn);
	onMagnetOn(next);
	magnetOff();
	nbFish ++;
}

static void withFish(){
	if(getTeam() == GREEN_TEAM){
		setCurrentLocation(391 + getRobotDistance(), 111);
		printf("Position en x : %f\n", 391 + getRobotDistance());
	} else {
		setCurrentLocation(391 - getRobotDistance(), 111);
		printf("Position en x : %f\n", 391 - getRobotDistance());
	}
	printf("Position du getPosition X = %f || Y = %f\n", getCurrentX(), getCurrentY());
	ffollow("water2net", releaseFish);
}

static void stop(){
	clearMotionQueue();
	queueSpeedChange(0, NULL);
	onFishCapture(NULL);
	onArmMid(withFish);
	armMid();
}

static void fish(){
	printf("Let's get some fish\n");
	setRobotDistance(0);
	onFishCapture(stop);
	if(getTeam() == GREEN_TEAM){
		queueSpeedChange(0.05, caca);
		queueStopAt(400, caca);
	} else {
		queueSpeedChange(-0.05, caca);
		queueStopAt(i-400, caca);
	}
}

static void schedulestep(){
	scheduleIn(2000, fishstep);
}

static void fishstep(){
	printf("Let's get some fish\n");
	if(getTeam() == GREEN_TEAM)
		setRobotDistance(100 * step);
	else
		setRobotDistance(-100 * step);
	onFishCapture(stop);
	if(step < 4) {
		step ++;
		if(getTeam() == GREEN_TEAM){
			queueSpeedChange(0.05, caca);
			queueStopAt(100 * step, schedulestep);
		} else {
			queueSpeedChange(-0.05, caca);
			queueStopAt(-100 * step, schedulestep);
		}
	} else {
		armUp();
	}
}

void startFishing(){
	onFishCapture(NULL);
	onArmUp(endFishingCallback);
	setRobotHeading(90);
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
	straight = 1;
	onFishCapture(NULL);
	onArmUp(endFishingCallback);
	setRobotHeading(90);
	onArmDown(fish);
	if(getTeam() == GREEN_TEAM)
		setTargetHeading(0, armDown);
	else
		setTargetHeading(180, armDown);
}

void onEndFishing(void (*callback)(void)){
	endFishingCallback = callback;
}
