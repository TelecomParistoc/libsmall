#include <librobot/robot.h>
#include <librobot/fisharm.h>
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <robotdriver/motordriver.h>
#include <stdlib.h>

static void stop(){
	clearMotionQueue();
	queueSpeedChange(0, NULL);
	armMid();
}

static void fish(){
	setRobotDistance(0);
	onFishCapture(stop);
	queueSpeedChange(0.1, NULL);
	queueStopAt(450, NULL);
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
