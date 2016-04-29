#include <pincers.h>
#include <pincersaction.h>
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <pathfollower/pathfollower.h>

static int first = 1;

static void deliver(){
	if(first){
		onOpenPincers(catch);
		first = 0;
	else{
		onOpenPincers(closePincers);
	}
	ffollow("rocks2start", openPincers);

static void goForward(){
	enableHeadingControl(0);
	queueSpeedChange(0.15, NULL);
}

static void stopAndCatch(){
	fastSpeedChange(0);
	enableHeadingControl(1);
	tryCapture();
}

void catch(){
	onTryCapture(deliver);
	setBlockingCallback(stopAndCatch);
	onOpenPincers(goForward);
	ffollow("water2rocks", openPincers);
}
