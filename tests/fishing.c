#include <pathfollower/pathfollower.h>
#include <robotdriver/motordriver.h>
#include <librobot/robot.h>
#include <librobot/fisharm.h>
#include <stdlib.h>
#include <stdio.h>

void moveToFish();
void moveWhileFish();
void moveToNet();
void startFishing();

int main() {
	initRobot();
	setCurrentLocation(180,1004);
	initFishAx12();
	struct robotPoint path[] = {
		{555, 1100},
		{842, 1100},
	};

	followPath(path, 2, 0, moveToFish);

	while(1);

	return 0;
}

void moveToFish(){
	struct robotPoint path[] =
	{
		{910, 166},
	//	{870, 120}
	};

	followPath(path, 1, 0, startFishing);
}

void moveWhileFish(){
	printf("Let's get some fish\n");
	struct robotPoint path[] =
	{
		{634, 120}
	};

	followPath(path, 1, 0, NULL);
}

void moveToNet(){
	struct robotPoint path[] =
	{
		{910, 166},
		{1213, 121}
	};
	followPath(path, 2, 0, magnetOff);
}

void startFishing(){
	onArmDown(waitForFish);
	onArmMid(moveToNet);
	onMagnetOff(magnetOn);
	onMagnetOn(armUp);
	moveWhileFish();
}
