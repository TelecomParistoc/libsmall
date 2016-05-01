#include <robotdriver/headingcontroller.h>
#include <pathfollower/pathFollower.hpp>
#include <librobot/pincersaction.h>
#include <librobot/pincers.h>
#include <librobot/fish.h>

//utils.hpp contient ways, actions et curPos
#include "utils.hpp"


void initWaysAndActions()
{
	ways = {"start2water", "water2net", "net2water", "water2net", "net2water", "water2net", "net2water", "water2net", "net2rocks", "rocks2start", "start2rocks", "rocks2start2"};

	actions.push_back(Action(&delayStart, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&startFishing, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&releaseFish, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&turn2, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&releaseFish, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&turn2, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&releaseFish, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&turn2, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&releaseFish, NULL, NULL, &fishStop, &fishHasFinished));
	actions.push_back(Action(&catchShells, NULL, NULL, &pincersStop, &pincersHasFinished));
	actions.push_back(Action(&openPincers, NULL, NULL, &pincersStop, &pincersHasFinished));
	actions.push_back(Action(&closePincers, NULL, NULL, &pincersStop, &pincersHasFinished));
	actions.push_back(Action(&openPincers, NULL, NULL, &pincersStop, &pincersHasFinished));
	setRGB(255, 0, 0);
}

void allume()
{
    std::cout<<"Jack grabed"<<std::endl;
    onGameStart(&go);
    /**A completer pour chaque robot**/
    onGameStop(&exitAndClean);
}

void endCallback()
{
	std::cout<<"Ending"<<std::endl;
	setRGB(255, 255, 0);

	clearMotionQueue();
    queueSpeedChange(0, nullptr);
	setTargetHeading(getRobotHeading(),NULL);
}
