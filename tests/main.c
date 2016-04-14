#include <robotdriver/toolboxdriver.h>
#include <librobot/fish.h>
#include <librobot/pincers.h>
#include <librobot/pincersaction.h>
#include <librobot/robot.h>
#include <pathfollower/pathfollower.h>
#include <stdio.h>

void jackOn(){
	printf("Jack plugged\n");
}

void start(){
	printf("Let's go !\n");
	waitFor(3000);
	ffollow("start2water", startFishing);
	while(!fishHasFinished())
		waitFor(50);
	fishStop();
	ffollow("water2net", releaseFish);
	while(!fishHasFinished())
		waitFor(50);
	fishStop();
	ffollow("net2water", turn2);
	while(!fishHasFinished())
		waitFor(50);
	fishStop();
	ffollow("water2net", releaseFish);
	while(!fishHasFinished())
		waitFor(50);
	fishStop();
	ffollow("net2water", turn2);
	while(!fishHasFinished())
		waitFor(50);
	fishStop();
	ffollow("water2net", releaseFish);
	while(!fishHasFinished())
		waitFor(50);
	fishStop();
	ffollow("net2water", turn2);
	while(!fishHasFinished())
		waitFor(50);
	fishStop();
	ffollow("water2net", releaseFish);
	while(!fishHasFinished())
		waitFor(50);
	fishStop();
	ffollow("net2rocks", catchShells);
	while(!pincersHasFinished())
		waitFor(50);
	pincersStop();
	ffollow("rocks2start", openPincers);
	while(!pincersHasFinished())
		waitFor(50);
	pincersStop();
	ffollow("start2rocks", closePincers);
	while(!pincersHasFinished())
		waitFor(50);
	pincersStop();
	ffollow("rocks2start2", openPincers);
}

int main(){
	initRobot();
	onGameStop(jackOn);
	onGameStart(start);
	while(1);
	return 0;
}
