#include <librobot/robot.h>
#include <robotdriver/toolboxdriver.h>

int main(){
	initRobot();
	setRGB(0, 0x66, 0xCC);
	while(1);
	return 0;
}
