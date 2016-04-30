#include <robotdriver/toolboxdriver.h>
#include <librobot/robot.h>
#include <stdio.h>

static void collisionDetect(int sensor) {
    printf("Obstacle detected from sensor %d\n", sensor);
}
static void collisionEnd(int sensor) {
    printf("No more obstacle in front of sensor %d\n", sensor);
}
static void gameStart() {
    printf("game start !\n");
}
static void gameStop() {
    printf("game stop !\n");
}


int main () {
    initRobot();

    onCollisionDetect(collisionDetect);
    onCollisionEnd(collisionEnd);

    onGameStart(gameStart);
    onGameStop(gameStop),

    while(1) {
        // config switch
        printf("Current config : %d, ", getTableConfig());
        // buttons test
        if(getTeam()==GREEN_TEAM)
            printf("Team : green, ");
        else
            printf("Team : purple, ");
        if(getMode()==MATCH_MODE)
            printf("Mode : match\n");
        else
            printf("Mode : test\n");

        waitFor(500);
    }
    return 0;
}
