#ifndef ROBOT_H
#define ROBOT_H

#ifdef __cplusplus
extern "C" {
#endif

// call actions from input text file
int readAndCall(FILE * file, char c);

void initRobot();

void stopGame();

#ifdef __cplusplus
}
#endif

#endif // ROBOT_H
