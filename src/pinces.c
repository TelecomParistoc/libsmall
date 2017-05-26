#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "pinces.h"
#include <robotdriver/driver.h>

int isTube()
{
	return 1;
}

void initPinces(){
	AX12setSpeed(ID_1, SPEED_1);
	AX12setTorque(ID_1, TORQUE_1);
	AX12setSpeed(ID_2, SPEED_2);
	AX12setTorque(ID_2, TORQUE_2);
	AX12setSpeed(ID_3, SPEED_3);
	AX12setTorque(ID_3, TORQUE_3);
	AX12setSpeed(ID_4, SPEED_4);
	AX12setTorque(ID_4, TORQUE_4);
	printf("Move MOTOR 1 to initial position\n");
	move_to(ID_1, POS_1_BOTTOM);
	printf("Move MOTOR 2 to initial position\n");
	move_to(ID_2, POS_2_HORIZONTAL);
	printf("Move MOTOR 3 to initial position\n");
	move_to(ID_3, POS_3_OPEN);
	printf("Move MOTOR 4 to initial position\n");
	move_to(ID_4, POS_4_OPEN);
	wait();
}

void catchOneTube(){
	int dist = 0;
	int tube = 0;
	while(dist <= 40)
	{
	    if(isTube()){
		tube = 1;
		break;
	    }
            setGoalMeanDist(10);
            dist += 10;
	}
	if(!tube && !isTube())
	     return;
	printf("[INFO] catch tube\n");
	move_to_block(ID_3, POS_3_CLOSE);
	wait();
}

void adjustAngle(){
	move_to_block(ID_1 , POS_1_MIDDLE);
	move_to_block(ID_2 , POS_2_VERTICAL);
}

void storeFirstTube(){
	// secondly, to go up to the middle for turning an angle
	move_to_block(ID_1, POS_1_TOP);
	// thirdly, to turn a angle
	move_to_block(ID_4, POS_4_CLOSE);

	move_to_block(ID_3, POS_3_OPEN;
	// seventhly, to lock the container
	move_to_block(ID_1, POS_1_BOTTOM);
	// eighthly, to release the tube
	move_to_block(ID_2, POS_2_HORIZONTAL);
	wait();
}

void storeSecondTube(){
	// secondly, to go up to the middle for turning an angle
	move_to_block(ID_1, POS_1_HIGH);
	// thirdly, to turn a angle
	move_to_block(ID_4, POS_4_OPEN);
	// fourthly, to continue going up to a higher place for the opening of the "lock"
	move_to_block(ID_1, POS_1_TOP);
	// fifthly, to open the lock
	move_to_block(ID_4, POS_4_CLOSE);
	// sixthly, to push up the tube to the container
	move_to_block(ID_3, POS_3_OPEN);
	// seventhly, to lock the container
	move_to_block(ID_1, POS_1_BOTTOM));
	// eighthly, to release the tube
	move_to_block(ID_2, POS_2_HORIZOTAL);
	wait();
}

void storeThirdTube(){
	// secondly, to go up to the middle for turning an angle
	move_to_block(ID_1, POS_1_HIGH);
	// thirdly, to turn a angle
	move_to_block(ID_4, POS_4_OPEN);
	// fourthly, to continue going up to a higher place for the opening of the "lock"
	move_to_block(ID_1, POS_1_TOP-3);
	// fifthly, to open the lock
	move_to_block(ID_4, POS_4_CLOSE);
	// sixthly, to push up the tube to the container
	move_to_block(ID_3, POS_3_OPEN);
	// seventhly, t lock the container
	move_to_block(ID_1, POS_1_BOTTOM);
	// eighthly, to release the tube
	move_to_block(ID_2, POS_2_HORIZONTAL)
	wait();
}

void putFirstTube()
{
	printf("[INFO] release tube\n");
	// getchar();
	move_to_block(ID_1, POS_1_BOTTOM);
	move_to_block(ID_3, POS_3_OPEN);
}

void putSecondTube()
{
	printf("[INFO] release tube\n");
	move_to_block(ID_1, POS_1_TOP);
	move_to_block(ID_3, POS_3_CLOSE);
	move_to_block(ID_4, POS_4_OPEN);
	move_to_block(ID_1, POS_1_HIGH);
	move_to_block(ID_4, POS_4_CLOSE);
	move_to_block(ID_1, POS_1_BOTTOM);
	move_to_block(ID_3, POS_3_OPEN);
}

void putLastTube()
{
	printf("[INFO] release tube\n");
	// getchar();
	move_to_block(ID_1, POS_1_TOP);
	move_to_block(ID_3, POS_3_CLOSE);
	move_to_block(ID_4, POS_4_OPEN);
	move_to_block(ID_1, POS_1_BOTTOM);
	move_to_block(ID_3, POS_3_OPEN);
}

void catchRocketTubes()
{
	catchOneTube();
        setGoalMeanDist(-DIST_ROCKET);
	adjustAngle();
	storeFirstTube();
        setGoalMeanDist(DIST_ROCKET);
	catchOneTube();
        setGoalMeanDist(-DIST_ROCKET);
	adjustAngle();
	storeSecondTube();
        setGoalMeanDist(DIST_ROCKET);
	catchOneTube();
        setGoalMeanDist(-DIST_ROCKET);
	adjustAngle();
	storeThirdTube();
        setGoalMeanDist(DIST_ROCKET);
	catchOneTube();
	adjustAngle();
}
