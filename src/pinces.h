#ifndef PINCES_H
#define PINCES_H

#define BAUDRATE 	115200

// Motor 1: rotate the hole bottom arm
#define ID_1		146
#define SPEED_1		20
#define TORQUE_1	100
#define POS_1_BOTTOM	80
#define POS_1_MIDDLE	50
#define POS_1_HIGH	20
#define POS_1_TOP	0
// Motor 2: rotate the bottom pince
#define ID_2		163
#define SPEED_2		40
#define TORQUE_2	100
#define POS_2_HORIZONTAL 0
#define POS_2_VERTICAL	90
// Motor 3: open/close the bottom pince
#define ID_3		20
#define SPEED_3		20
#define TORQUE_3	100
#define POS_3_WIDE	60
#define POS_3_OPEN	28
#define POS_3_CLOSE	-10
// Motor 4: open/close the top pince
#define ID_4		25
#define SPEED_4		20
#define TORQUE_4	100
#define POS_4_OPEN	20
#define POS_4_CLOSE	80

void initPinces();
void catchOneTube();
void storeFirstTube();
void storeSecondTube();
void storeThirdTube();
void putFirstTube();
void putSecondTube();
void putLastTube();

void catchRocketTubes();

#endif // PINCES_H
