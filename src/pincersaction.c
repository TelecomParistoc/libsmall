#include <pincers.h>
#include <pincersaction.h>
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <pathfollower/pathfollower.h>

static void stopAndCatch();

static int first = 1;

static void getSecond(){
	setBlockingCallback(stopAndCatch);
	enableHeadingControl(0);
	queueSpeedChange(0.15, NULL);
}

static void catchSecond() {
	ffollow("start2rocks", getSecond);
}

static void deliver(){
	setCurrentLocation(getPosInCorner(getCurrentHeading()).x, getPosInCorner(getCurrentHeading()).y);
	if(first){
		onOpenPincers(catchSecond);
		first = 0;
	else{
		onOpenPincers(closePincers);
	}
	if(first)
		ffollow("rocks2start", openPincers);
	else
		ffollow("rocks2start2", openPincers);

static void getFirst(){
	if(getTableConfiguration == 4) {
		closePincers();
		ffollow("rocks2start", catchSecond);
		first = 0;
	}
	enableHeadingControl(0);
	queueSpeedChange(0.15, NULL);
}

static void stopAndCatch(){
	fastSpeedChange(0);
	enableHeadingControl(1);
	tryCapture();
}

void catchShells(){
	onTryCapture(deliver);
	setBlockingCallback(stopAndCatch);
	onOpenPincers(getFirst);
	ffollow("water2rocks", openPincers);
}
