#include <stdlib.h>
#include <librobot/robot.h>
#include <librobot/pincers.h>
#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>

static void foo(){
	queueSpeedChange(0.1, NULL);
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
		setBlockingCallback(tryCapture);
		onOpenPincers(foo);
		openPincers();
	}
	while(1);
	return 0;
}
