#include <stdlib.h>
#include <librobot/robot.h>
#include <librobot/pincers.h>
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>

static void goForward(){
	enableHeadingControl(0);
	queueSpeedChange(0.15, NULL);
}

static void stopAndCatch(){
	fastSpeedChange(0);
	enableHeadingControl(1);
	tryCapture();
}

int main (int argc, char *argv[]) {
	initRobot();
	onTryCapture(testCallback);
	if(argc == 2){
		if(atoi(argv[1]) == 2)
			tryCapture();
		if(atoi(argv[1]) == 1)
			openPincers();
		if(atoi(argv[1]) == 0)
			closePincers();
	}
	else {
		setBlockingCallback(stopAndCatch);
		onOpenPincers(goForward);
		openPincers();
	}
	while(1);
	return 0;
}
