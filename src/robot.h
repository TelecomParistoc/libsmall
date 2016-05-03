#ifndef ROBOT_H
#define ROBOT_H

#ifdef __cplusplus
extern "C" {
#endif

/* initialize the robot and make it ready to run. This MUST BE called before any
 * other operations */
void initRobot();

/* calls the given function at the start of the game (when the start jack is
 * unplugged) */
void onGameStart(void (*callback)(void));
void onGameStop(void (*callback)(void));

/* calls the given function when a collision sensor detects a new obstacle.
 * the callback should be like void myCallback(int collisionSensor) {...}. The
 * argument collisionSensor is the sensor that detected a new obstacle */
void onCollisionDetect(void (*callback)(int));
/* calls the given function when a collision sensor stops detecting an obstacle.
 * the callback should be like void myCallback(int collisionSensor) {...}. The
 * argument collisionSensor is the sensor that stopped detecting an obstacle */
void onCollisionEnd(void (*callback)(int));

#define REAR_COLLISION 0
#define FRONT_LEFT_COLLISION 1
#define FRONT_RIGHT_COLLISION 2

typedef enum { all, front, rear, left, right, none } collisionConfig_t;
void setActiveDetectors(collisionConfig_t config);

/* check if a robot is detected in front (when moving forward)*/
int isRobotFront();
/* check if a robot is detected behind (when moving backward) */
int isRobotBehind();

/* returns the current table configuration, describing how the shells are placed */
int getTableConfig();

/* set the color of the eyes (red greed and blue between 0 and 255) */
void setRGB(char red, char green, char blue);

/* Set by the main to allow jumping to another step */
void onJump(void (*callback)(int));
void jumpTo(int step);

/* returns the selected team */
int getTeam();
/* teams defined as : */
#define GREEN_TEAM 0
#define PURPLE_TEAM 1

/* returns the selected mode (test or match) */
int getMode();
/* mode defined as : */
#define MATCH_MODE 0
#define TEST_MODE 1

#ifdef __cplusplus
}
#endif

#endif
