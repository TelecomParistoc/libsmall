#include <robotdriver/motordriver.h>
#include <pathfollower/pathfollower.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/motioncontroller.h>
#include <librobot/fisharm.h>
#include <librobot/robot.h>
#include <stdio.h>


void move1();
void move2();


void onTheEndOfTheFirstRoad()
{
    printf("I've travelled a long way, go fishing !\n");
	initFishAx12();
	onArmDown(waitForFish);
    armDown();
    onArmMid(move2);
}

void onTheEndOfTheSecondRoad()
{
    printf("I've travelled a long way, go releasing !\n");
    onMagnetOff(magnetOn);
	onMagnetOn(armUp);
    magnetOff();
}

void move1()
{
    struct robotPoint path[] =
    {
        {250, 300},
        {350, 100},
        {500, 20},
	    {550, 10}
    };

    followPath(path, 4, 0, onTheEndOfTheFirstRoad);
}

void move2()
{
    struct robotPoint path[] =
    {
        {600, 50},
        {800, 50},
        {1000, 15},
	    {1050, 10}
    };

    followPath(path, 4, 0, onTheEndOfTheSecondRoad);
}

int main()
{
    initRobot();
    setCurrentLocation(0,900);
    move1();

    while(1);

    return 0;
}
