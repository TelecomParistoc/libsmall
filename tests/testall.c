#include <pathfollower/pathfollower.h>
#include <robotdriver/toolboxdriver.h>
#include <librobot/robot.h>
#include <librobot/fish.h>
#include <librobot/pincersaction.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	initRobot();
	onEndFishing(catchShells);
	if(atoi(argv[1]))
		startFishingStep();
	else
		startFishing();
	while(1);
	return 0;
}
