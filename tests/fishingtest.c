#include <librobot/fisharm.h>
#include <librobot/robot.h>
#include <robotdriver/toolboxdriver.h>
#include <stdio.h>

static void waitf();
	
static void check(){
	if (hasFish())
		armMid();
	else
		waitf();
}

static void delay(){
	onFishCapture(NULL);
	scheduleIn(1000, check);
}

static void waitf(){
	onFishCapture(delay);
}

int main () {
	initRobot();
	printf("C'est parti\n");
	onArmDown(waitf);
	onArmMid(magnetOff);
	onMagnetOff(magnetOn);
	onMagnetOn(armUp);
	armDown();
	while(1);
	return 0;
}
