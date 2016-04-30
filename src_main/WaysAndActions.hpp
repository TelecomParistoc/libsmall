#include <pathfollower/pathFollower.hpp>
#include "Action.hpp"

/**Attention : ceci n'est qu'un exemple complètement irréaliste.
* Chaque robot doit avoir son propre fichier ways_and_actions qui doit être rempli en conséquences
**/

std::vector<std::string> ways = {"move_cubes_go_fish","water2net","net2water","water2net","net2water","water2net","net2rocks","rocks2rocks"};
std::vector<Action> actions;
std::pair<double,double> curPos = std::pair<double,double>(40,1000);

void initWaysAndActions()
{
    actions.push_back(Action());
    actions.push_back(Action(&pecher_start,&pecher_pause,&pecher_continue,&pecher_isFinished));
    actions.push_back(Action(&relacher_start,&relacher_pause,&relacher_continue,&relacher_isFinished));
    //etc ...

    /**A decommenter pour le gros robot**/
    /**PathFollower::setRadiusPositiveSpeed(180);
    PathFollower::setRadiusNegativeSpeed(120);
    **/
}
