#include <librobot/robot.h>
#include <librobot/fisharm.h>
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <robotdriver/motordriver.h>
#include <pathfollower/pathfollower.h>
#include <stdlib.h>
#include <stdio.h>

static void realeaseFish();

static int nbFish = 0;

static void caca() {
	printf("lol\n");
}

static void withFish2(){
	setCurrentLocation(800 + getRobotDistance(), 114);
	ffollow("water2net", realeaseFish);
}

static void stop2(){
	clearMotionQueue();
	queueSpeedChange(0, NULL);
	onArmMid(withFish2);
	armMid();
}

static void fish2(){
	printf("Let's get some fish\n");
	onArmDown(NULL);
	setRobotDistance(0);
	onFishCapture(stop2);
	queueSpeedChange(-0.05, caca);
	queueStopAt(-400, caca);
}

static void turn2(){
	onArmDown(fish2);
	setTargetHeading(0, armDown);
}

static void realeaseFish(){
	onMagnetOff(drop);
	onArmMid(magnetOn);
	onMagnetOn(armUp);
	magnetOff();
	nbFish ++;
	if(nbFish < 4){
		ffollow("net2water", turn2);
	}
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
	printf("Let's get some fish\n");
	onArmDown(NULL);
	setRobotDistance(0);
	onFishCapture(stop);
	queueSpeedChange(0.05, caca);
	queueStopAt(400, caca);
}

static void turn(){
	setRobotHeading(90);
	onArmDown(fish);
	setTargetHeading(0, armDown);
}

int main(){
	initRobot();
	setCurrentLocation(41, 1003);
	ffollow("start2water", turn);
	while(1);
	return 0;
}
