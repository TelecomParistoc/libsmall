#include <pathfollower/pathFollower.hpp>
#include <librobot/fish.h>
#include <librobot/pincersaction.h>
#include <librobot/pincers.h>
#include "Action.hpp"

/**Attention : ceci n'est qu'un exemple complètement irréaliste.
 * Chaque robot doit avoir son propre fichier ways_and_actions qui doit être rempli en conséquences
 **/

std::vector<std::string> ways = {"start2water", "water2net", "net2water", "water2net", "net2water", "water2net", "net2water", "water2net", "net2rocks"};
std::vector<Action> actions;
std::pair<double,double> curPos = std::pair<double,double>(41,1003);

void initWaysAndActions()
{
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

    setRGB(255, 0, 0);
}

bool start = false;

void go()
{start = true;}

void allume()
{
    std::cout<<"Jack grabed"<<std::endl;
    onGameStart(&go);
    /**A completer pour chaque robot**/
    onStopGame(&exitAndClean);
}

void exitAndClean()
{
    std::cout<<"Exiting"<<std::endl;
    exit(0);
}
