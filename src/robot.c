#include <robotdriver/driver.h>
#include <stdlib.h>
#include <wiringPi.h>

// call before game starts
void initRobot() {
        wiringPiSetup();
        initAX12(115200);
        initRoof();


}

// call after 90 sec of game
void stopGame() {
        stopRobot();
        AX12setTorque(0xFE, 0);
}
