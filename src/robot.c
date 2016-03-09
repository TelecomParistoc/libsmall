#include "robot.h"

void fishSensorManager();

static void collisionsCallback() {

}
static void sensorsCallback() {
	fishSensorManager();
}

void initRobot() {
	initToolboxDriver();
	initMotionController();

	setRobotDistance(0);
	setRobotHeading(0);
	axReset();

	enableSensorCallback(1);
	disableSensorCallback(2);
	disableSensorCallback(3);
	disableSensorCallback(4);
	disableSensorCallback(5);
	setSensorsCallback(sensorsCallback);

	disableCollisionCallback(1);
	disableCollisionCallback(2);
	enableCollisionCallback(3);
	enableCollisionCallback(4);
	enableCollisionCallback(5);
	setCollisionsCallback(collisionsCallback);
}
