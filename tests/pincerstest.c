#include <stdlib.h>
#include <librobot/robot.h>
#include <librobot/pincers.h>

int main (int argc, char *argv[]) {
	initRobot();
	onTryCapture(testCallback);
	if(atoi(argv[1]) == 2)
		tryCapture();
	if(atoi(argv[1]) == 1)
		openPincers();
	if(atoi(argv[1]) == 0)
		closePincers();
	return 0;
}
