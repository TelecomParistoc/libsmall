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

static void caca() {
	printf("lol\n");
}

static void withFish2(){
	setCurrentLocation(800 + getRobotDistance(), 114);
	printf("Position en x : %f\n", 800 + getRobotDistance());
	printf("Pos de getPosition :  X = %f || Y = %f\n)", getCurrentX(), getCurrentY());
	ffollow("water2net", releaseFish);
}

static void stop2(){
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
	queueSpeedChange(-0.05, caca);
	queueStopAt(-400, caca);
}

static void turn2(){
	onArmDown(fish2);
	setTargetHeading(0, armDown);
}

static void next(){
	if(nbFish < 4)
		ffollow("net2water", turn2);
	else
		armUp();
}

static void releaseFish(){
	onMagnetOff(drop);
	onArmMid(magnetOn);
	onMagnetOn(next);
	magnetOff();
	nbFish ++;
}

static void withFish(){
	setCurrentLocation(391 + getRobotDistance(), 111);
	printf("Position en x : %f\n", 391 + getRobotDistance());
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
	queueSpeedChange(0.05, caca);
	queueStopAt(400, caca);
}

void startFishing(){
	onFishCapture(NULL);
	setRobotHeading(90);
	onArmDown(fish);
	setTargetHeading(0, armDown);
}
