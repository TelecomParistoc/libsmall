#include <pathfollower/pathFollower.hpp>
#include <librobot/fish.h>
#include <librobot/pincersaction.h>
#include "Action.hpp"

/**Attention : ceci n'est qu'un exemple complètement irréaliste.
* Chaque robot doit avoir son propre fichier ways_and_actions qui doit être rempli en conséquences
**/

std::vector<std::string> ways = {"start2water", };
std::vector<Action> actions;
std::pair<double,double> curPos = std::pair<double,double>(41,1003);

void initWaysAndActions()
{
    actions.push_back(Action());
    actions.push_back(Action(&startFishing, NULL, NULL, &fishStop, &fishHasFinished));
    actions.push_back(Action(&releaseFish, NULL, NULL, &fishStop, &fishHasFinished));
    actions.push_back(Action(&turn2, NULL, NULL, &fishStop, &fishHasFinished));
}
