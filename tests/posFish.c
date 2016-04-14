#include <librobot/robot.h>
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <stdlib.h>

static void recalibrate(){
	fastSpeedChange(0);
	enableHeadingControl(1);
	setRobotDistance(0);
	queueSpeedChange(0.15, NULL);
	queueStopAt(30, NULL);
}
	

int main(){
	initRobot();
	setBlockingCallback(recalibrate);
	enableHeadingControl(0);
	queueSpeedChange(-0.15, NULL);
	while(1);
	return 0;
}
