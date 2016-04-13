#include <librobot/robot.h>
#include <robotdriver/toolboxdriver.h>

int main(){
	initRobot();
	setRGB(0, 0x16, 0x7C);
	while(1);
	return 0;
}
