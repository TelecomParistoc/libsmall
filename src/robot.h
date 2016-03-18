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

void setRGB(char red, char green, char blue);

#ifdef __cplusplus
}
#endif

#endif
