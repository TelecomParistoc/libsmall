#include <librobot/robot.h>
#include <librobot/fisharm.h>
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <robotdriver/motordriver.h>
#include <pathfollower/pathfollower.h>
#include <stdlib.h>
#include <stdio.h>

static void caca() {
	printf("lol\n");
}

static void realeaseFish(){
	onMagnetOff(drop);
	onArmMid(magnetOn);
	onMagnetOn(armUp);
	magnetOff();
}

static void withFish(){
	setCurrentLocation(391 + getRobotDistance(), 111);
	ffollow("water2net", realeaseFish);
}

static void stop(){
	clearMotionQueue();
	queueSpeedChange(0, NULL);
	onArmMid(withFish);
	armMid();
}

static void fish(){
	setRobotDistance(0);
	onFishCapture(stop);
	queueSpeedChange(0.1, caca);
	queueStopAt(450, caca);
}

static void turn(){
	setRobotHeading(90);
	onArmDown(fish);
	setTargetHeading(0, armDown);
}

static void recalibrate(){
	setBlockingCallback(NULL);
	fastSpeedChange(0);
	enableHeadingControl(1);
	setRobotDistance(0);
	queueSpeedChange(0.15, NULL);
	queueStopAt(70, turn);
}

int main(){
	initRobot();
	setBlockingCallback(recalibrate);
	enableHeadingControl(0);
	queueSpeedChange(-0.15, NULL);
	while(1);
	return 0;
}
