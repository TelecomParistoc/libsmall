#include <pathfollower/pathfollower.h>
#include <robotdriver/toolboxdriver.h>
#include <librobot/robot.h>
#include <librobot/fish.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	initRobot();
	startFishing();
	while(1){
		waitFor(100);
		printf("Position du getPosition X = %f || Y = %f\n", getCurrentX(), getCurrentY());
	}
	return 0;
}
