#include <pathfollower/pathFollower.hpp>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/motioncontroller.h>
#include <robotdriver/toolboxdriver.h>
#include <robotdriver/motordriver.h>
#include <librobot/robot.h>
#include <iostream>
#include <chrono>

//g++ testBlocked.cpp -o testBlocked -lrobot -lrobotdriver -lpathfollower -std=c++11

std::vector<std::string> ways = {"test_stopping","test_stopping"};
//std::vector<Action> actions = {Action(),Action("pecher"),Action("relacher"),Action("pecher"),Action("relacher"),Action("pecher"),Action("relacher"),Action(),Action()};

bool start = false;
bool started = false;
bool blocked = false;
bool seeBlocked = false;

int way = 0;
std::pair<double,double> curPos = std::pair<double,double>(44,520);

void go()
{start = true;}

void checkCollisionAndReact(int)
{seeBlocked = true;}

void endWay()
{
    std::cout<<"End of way "<<way<<std::endl;
    curPos = PathFollower::getCurrentPos();
    PathFollower::setCurrentPosition(curPos.first,curPos.second);
    way++;
    if(way<ways.size())
        ffollow(ways[way].c_str(), &endWay);
}

int main()
{
    initRobot();
    setRGB(255, 0, 0);

    ///TODO: mettre les callbacks appropriés
    //setJackCallback(&go);
    start = true;
    onCollisionDetect(&checkCollisionAndReact);

    setMoveStartCallback(&PathFollower::updateAngleStartingMove);
    setMoveEndCallback(&PathFollower::updatePositionEndingMove);
    setCurrentLocation(curPos.first,curPos.second);
    PathFollower::resetPosition(curPos);

    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::milliseconds milliseconds;
    Clock::time_point clk_start = Clock::now();

    double seconds = 90;

    while(std::chrono::duration_cast<milliseconds>(Clock::now()-clk_start).count()<seconds*1000)
    {
        if(start&&!started)
        {
            printf("Start\n");
            started = true;
            ffollow(ways[way].c_str(), &endWay);
        }

        if(seeBlocked)
            if(PathFollower::isSpeedPositive())
            {
                if(!isRobotFront())
                    seeBlocked = false;
                else
                    if(!PathFollower::isPaused())
                    {
                        blocked = true;
                        PathFollower::pause();
                    }
            }
            else
            {
                if(!isRobotBehind())
                    seeBlocked = false;
                else
                    if(!PathFollower::isPaused())
                    {
                        blocked = true;
                        PathFollower::pause();
                    }
            }

        if(!seeBlocked)
            if(blocked)
            {
                blocked = false;
                PathFollower::continueMoving();
            }

        curPos = PathFollower::getCurrentPos();
        std::cout<<curPos.first<<" "<<curPos.second<<" "<<seeBlocked<<" "<<blocked<<std::endl;

        waitFor(100);
    }

    return 0;
}
