#include <librobot/fisharm.h>
#include <librobot/robot.h>
#include <stdio.h>

int main () {
	initRobot();
	initFishAx12();
	onFishCapture(armMid);
	armDown();
	while(1);
	return 0;
}
