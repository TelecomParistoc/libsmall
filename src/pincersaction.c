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
	if(first) {
		if(getTableConfiguration != 4)
			onOpenPincers(catchSecond);
		else
			onOpenPincers(closePincers);
		first = 0;
		ffollow("rocks2start", openPincers);
	} else {
		onOpenPincers(closePincers);
		ffollow("rocks2start2", openPincers);
	}

	static void getFirst(){
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
