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
	if(isTube())
	    printf("capteur de proximite a faire !");

	printf("[INFO] catch tube\n");
	// firstly, to catch tube by using motor 20
	move_to_block(ID_3, POS_3_CLOSE);
	wait();
}

void storeFirstTube(){
	// secondly, to go up to the middle for turning an angle
	move_to_block(ID_1, POS_1_MIDDLE);
	// thirdly, to turn a angle
	move_to_block(ID_2, POS_2_VERTICAL);

	move_to_block(ID_1, POS_1_TOP);
	// seventhly, to lock the container
	move_to_block(ID_4, POS_4_CLOSE);
	// eighthly, to release the tube
	move_to_block(ID_3, POS_3_OPEN);
	// ninethly, to go back to the start place
	move_to_block(ID_1, POS_1_BOTTOM);
	// tenthly,  to turn an angle for catching a new tube.
	move_to_block(ID_2, POS_2_HORIZONTAL);
	wait();
}

void storeSecondTube(){
	// secondly, to go up to the middle for turning an angle
	move_to_block(ID_1, POS_1_MIDDLE);
	// thirdly, to turn a angle
	move_to_block(ID_2, POS_2_VERTICAL);
	// fourthly, to continue going up to a higher place for the opening of the "lock"
	move_to_block(ID_1, POS_1_HIGH);
	// fifthly, to open the lock
	move_to_block(ID_4, POS_4_OPEN);
	// sixthly, to push up the tube to the container
	move_to_block(ID_1, POS_1_TOP);
	// seventhly, to lock the container
	move_to_block(ID_4, POS_4_CLOSE);
	// eighthly, to release the tube
	move_to_block(ID_3, POS_3_OPEN);
	// ninethly, to go back to the start place
	move_to_block(ID_1, POS_1_BOTTOM);
	// tenthly,  to turn an angle for catching a new tube.
	move_to_block(ID_2, POS_2_HORIZONTAL);
	wait();
}

void storeThirdTube(){
	// secondly, to go up to the middle for turning an angle
	move_to_block(ID_1, POS_1_MIDDLE);
	// thirdly, to turn a angle
	move_to_block(ID_2, POS_2_VERTICAL);
	// fourthly, to continue going up to a higher place for the opening of the "lock"
	move_to_block(ID_1, POS_1_HIGH);
	// fifthly, to open the lock
	move_to_block(ID_4, POS_4_OPEN);
	// sixthly, to push up the tube to the container
	move_to_block(ID_1, POS_1_TOP-3);
	// seventhly, to lock the container
	move_to_block(ID_4, POS_4_CLOSE);
	// eighthly, to release the tube
	move_to_block(ID_3, POS_3_OPEN);
	// ninethly, to go back to the start place
	move_to_block(ID_1, POS_1_BOTTOM);
	// tenthly,  to turn an angle for catching a new tube.
	move_to_block(ID_2, POS_2_HORIZONTAL);
	wait();
}

void putFirstTube()
{

	printf("[INFO] release tube\n");
	// getchar();
	move_to_block(ID_2, POS_2_VERTICAL);
	move_to_block(ID_1, POS_1_TOP);
	move_to_block(ID_3, POS_3_CLOSE);
	move_to_block(ID_4, POS_4_OPEN);
	move_to_block(ID_1, POS_1_HIGH);
	move_to_block(ID_4, POS_4_CLOSE);
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
	storeFirstTube();
	catchOneTube();
	storeSecondTube();
	catchOneTube();
	storeThirdTube();
	catchOneTube();
}
