#include <librobot/robot.h>
#include <robotdriver/toolboxdriver.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	initRobot();
	setRGB(atoi(argv[1]),atoi(argv[2]), atoi(argv[3]));
	while(1);
	return 0;
}
