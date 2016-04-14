#include <stdlib.h>
#include "robot.h"
#include "pincers.h"

int main (int argc, char *argv[]) {
	initRobot();
	onClosePincers(testCallback());
	if(atoi(argv[1]))
		openPincers();
	else
		closePincers();
	return 0;
}
