#include <vector>
#include <string>

#include "Action.hpp"

std::vector<std::string> ways;
std::vector<Action> actions;
std::pair<double,double> curPos = std::pair<double,double>(41,1003);


bool isMovingToAction = false;
bool started = false;
bool blocked = false;
bool pausePath = false;
bool seeBlocked = false;

int way = -1;

void checkCollisionAndReact(int)
{seeBlocked = true;}

void endWay()
{
	std::cout<<"End of way "<<way<<std::endl;
	way++;
	if(way<(int)ways.size())
		actions[way].start();
	isMovingToAction = false;
}

void endAction()
{
	std::cout<<"End of action "<<way<<std::endl;
	curPos = PathFollower::getCurrentPos();
	PathFollower::setCurrentPosition(curPos.first,curPos.second);
	if(way<(int)ways.size())
		ffollow(ways[way].c_str(), &endWay);
	isMovingToAction = true;
}

bool start = false;

void go()
{
	std::cout<<"GO !"<<std::endl;
	start = true;
	endWay();
}

void exitAndClean()
{
    std::cout<<"Exiting"<<std::endl;
    exit(0);
}
