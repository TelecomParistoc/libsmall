#include <librobot/fisharm.h>
#include <librobot/robot.h>
#include <robotdriver/toolboxdriver.h>
#include <stdio.h>

int main () {
	initRobot();
//	printf("Pos 121 : %d\n", axGetPosition(121));
	printf("Pos 148 : %d\n", axGetPosition(148));
	/*initFishAx12();
	onFishCapture(armMid);
	armDown();*/
	while(1);
	return 0;
}
