#include <librobot/fisharm.h>
#include <librobot/robot.h>
#include <robotdriver/toolboxdriver.h>
#include <stdio.h>

int main () {
	initRobot();
	printf("C'est parti\n");
	onArmDown(waitForFish);
	onArmMid(magnetOff);
	onMagnetOff(magnetOn);
	onMagnetOn(armUp);
	armDown();
	while(1);
	return 0;
}
