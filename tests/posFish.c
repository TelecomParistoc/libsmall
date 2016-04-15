#include <librobot/robot.h>
#include <librobot/fisharm.h>
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <stdlib.h>

static void stop(){
	clearMotionQueue();
	queueSpeedChange(0);
	armMid();
}

static void fish(){
	setRobotHeading(0);
	setRobotDistance(0);
	queueSpeedChange(0.10, NULL);
	queueStopAt(450, NULL);

static void turn(){
	setRobotHeading(90);
	onArmDown(fish);
	onFishCapture(stop);
	setTargetHeading(0, armDown);

static void recalibrate(){
	fastSpeedChange(0);
	enableHeadingControl(1);
	setRobotDistance(0);
	queueSpeedChange(0.15, NULL);
	queueStopAt(30, turn);
}

int main(){
	initRobot();
	setBlockingCallback(recalibrate);
	enableHeadingControl(0);
	queueSpeedChange(-0.15, NULL);
	while(1);
	return 0;
}
