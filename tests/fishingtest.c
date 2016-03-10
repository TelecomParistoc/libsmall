#include <libsmall/fisharm.h>
#include <libsmall/robot.h>
#include <stdio.h>

int main () {
	initRobot();
	initFishAx12();
	onFishCapture(armMid);
	armDown();
	while(1);
	return 0;
}
