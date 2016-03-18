#include <robotdriver/motordriver.h>
#include <pathfollower/pathfollower.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/motioncontroller.h>
#include <librobot/fisharm.h>
#include <librobot/robot.h>
#include <stdio.h>


void onTheEndOfTheRoad()
{
    printf("I've travelled a long way, go fishing !\n");
	initFishAx12();
	onArmDown(waitForFish);
    armDown();
}

int main()
{
    struct robotPoint path[] =
    {
        {250, 300},
        {350, 100},
        {500, 20},
	    {550, 10}
    };
    
    initRobot();
    setCurrentLocation(0,900);
    followPath(path, 4, 0, onTheEndOfTheRoad);

    while(1);

    return 0;
}
