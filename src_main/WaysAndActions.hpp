#include <robotdriver/headingcontroller.h>
#include <robotdriver/motioncontroller.h>
#include <pathfollower/pathFollower.hpp>
#include <robotdriver/toolboxdriver.h>
#include <librobot/pincersaction.h>
#include <librobot/pincers.h>
#include <librobot/fish.h>
#include <time.h>

//utils.hpp contient ways, actions et curPos
#include "utils.hpp"


static bool hasBegun = false;
static bool light = true;

void toggleLed()
{
	if(!hasBegun)
	{
		scheduleIn(200, toggleLed);
		setLED(3, light);
		light = 1-light;
	}
	else
		setLED(3, 1);
}

void initWaysAndActions()
{
	curPos = std::pair<double,double>(196, 940);
	ways = {"start2water", "water2net", "net2water", "water2net", "net2water", "water2net", "net2water", "water2net", "net2rocks", "rocks2rocks", "rocks2start", "trololo", "nofish", "rocks2rocks", "rocks2start", "notime", "trololo"};

	actions.push_back(Action(&delayStart, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&startFishing, &pauseFish, &resumeFish, &fishStop, &fishHasFinished));
	actions.push_back(Action(&releaseFish, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&turn2, &pauseFish, &resumeFish, &fishStop, &fishHasFinished));
	actions.push_back(Action(&releaseFish, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&turn2, &pauseFish, &resumeFish, &fishStop, &fishHasFinished));
	actions.push_back(Action(&releaseFish, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&turn2, &pauseFish, &resumeFish, &fishStop, &fishHasFinished));
	actions.push_back(Action(&releaseFish, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&faceShell, NULL, NULL, &pincersStop, &pincersHasFinished));
	actions.push_back(Action(&openPincers, NULL, NULL, &pincersStop, &pincersHasFinished));
	actions.push_back(Action(&openPincers, NULL, NULL, &pincersStop, &pincersHasFinished));
	actions.push_back(Action(&delayStart, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&faceShell, NULL, NULL, &pincersStop, &pincersHasFinished));
	actions.push_back(Action(&openPincers, NULL, NULL, &pincersStop, &pincersHasFinished));
	actions.push_back(Action(&openPincers, NULL, NULL, &pincersStop, &pincersHasFinished));
	actions.push_back(Action(&openPincers, NULL, NULL, &pincersStop, &pincersHasFinished));

	setRGB(255, 0, 0);
	setLED(1,0);
	setLED(2,0);
	setLED(3,0);
	toggleLed();

	enableHeadingControl(0);
}

void jump(int w)
{
	std::cout<<"Jumping to "<<w<<" and current : "<<way<<std::endl;
	way = w;
}

void go()
{
	std::cout<<"GO"<<std::endl;
	enableHeadingControl(1);
	start = true;
	setLED(2,1);
	endWay();
}

void allume()
{
    std::cout<<"Jack grabed"<<std::endl;
    onGameStart(&go);
    /**A completer pour chaque robot**/
    onGameStop(&exitAndClean);

	check_mode(); //defined in utils.hpp => check the service and stop it

	onJump(&jump);
	setGetTimeCallback(&getTime);

	hasBegun = true;

	srand(time(NULL));
	if(rand()%100==1)
		setLED(1, 1);
}

void endCallback()
{
	std::cout<<"Ending"<<std::endl;
	setRGB(255, 255, 0);

	forceStop(1);
	setTargetHeading(getRobotHeading(),NULL);

	setLED(1,1);
	setLED(2,0);
	setLED(3,0);

	axReset();

	waitFor(1000);
}
