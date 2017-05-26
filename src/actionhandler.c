#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <robotdriver/movecontroller.h>
#include <robotdriver/motordriver.h>
#include <robotdriver/timing.h>
#include "robotdefs.small.h"
#include "pinces.h"

#define TAILLE_MAX 32
#define TAILLE_COORDONNEES 5
#define RADIUS 30
#define STARTRADIUS 30
#define OFFSET_X_BIG 1320
#define OFFSET_Y_BIG 180
#define OFFSET_X_SMALL 713
#define OFFSET_Y_SMALL 256

// 0: blue, 1: yellow
static int team = 0;
// 0: translation, 1: rotation
static int mov = 0;
// 0: forward, 1: backward
static int dir = 0;
// nombre cylindres dans petit robot 
//(hors fusée)
static int nbrCylindre = 0;

int readAndCall(FILE * file, char c)
{
    if((c >= '0') && (c <= '9')) {
	if(!mov){
    	    char Xcoord[TAILLE_COORDONNEES];
    	    char Ycoord[TAILLE_COORDONNEES];
    	    Xcoord[0] = c;
    	    int i = 1;
    	    while((c = fgetc(file)) != ' ')
    	        Xcoord[i++] = c;
    	    i = 0;
    	    while((c = fgetc(file)) != '\n')
    	        Ycoord[i++] = c;
    	    int x = atoi(Xcoord);
    	    int y = atoi(Ycoord);

            // offset
            if(!team) { // blue
                if(SIZE) { // big
                    x -= OFFSET_X_BIG;
                    y -= OFFSET_Y_BIG;
                } else { // small
                    x -= OFFSET_X_SMALL;
                    y -= OFFSET_Y_SMALL;
                }
            } else { // yellow
                if(SIZE) { // big
                    x += OFFSET_X_BIG;
                    y -= OFFSET_Y_BIG;
                } else { // small
                    x += OFFSET_X_SMALL;
                    y -= OFFSET_Y_SMALL;
                }
            }

    	    printf("[FILE] go to [%d,%d]\n", x, y);
    	    point_t dest = {x, y};
	    if(!dir)
                goForward(&dest);
	    else
		goBackward(&dest);
            return 0;
	}
        else {
    	    char rot_str[TAILLE_COORDONNEES];
    	    rot_str[0] = c;
    	    int i = 1;
    	    while((c = fgetc(file)) != '\n')
    	        rot_str[i++] = c;
    	    int rot = atoi(rot_str);
	    if(rot < 0)
		rot += 3600;
    	    printf("[FILE] go to [%ddeg]\n", rot / 10);
            rotate(rot);
            return 0;
	}
    }
    else if(c == 'I'){
        printf("[FILE] It's an I \n");
    	char initXchar[TAILLE_COORDONNEES];
    	char initYchar[TAILLE_COORDONNEES];
    	char initAchar[TAILLE_COORDONNEES];
    	initXchar[0] = c;
    	int i = 1;
    	while((c = fgetc(file)) != ' ')
    	    initXchar[i++] = c;
    	i = 0;
    	while((c = fgetc(file)) != '\n')
    	    initYchar[i++] = c;
    	i = 0;
    	while((c = fgetc(file)) != '\n')
    	    initAchar[i++] = c;
    	int x = atoi(initXchar);
    	int y = atoi(initYchar);
    	int a = atoi(initAchar);
	setHeading(a);
	printf("[FILE] init [%d,%d] %d\n", x, y, a);
        return 0;
    }
    while(fgetc(file) != '\n');
    // More forward
    if(c == 'A'){
        printf("[FILE] It's an A \n");
	mov = 0;
	dir = 0;
    }
    // Move backward
    else if(c == 'R'){
        printf("[FILE] It's a R \n");
	mov = 0;
	dir = 1;
    }
    // Rotate
    else if(c == 'T'){
        printf("[FILE] It's a T \n");
	mov = 1;
    }
    // Take four cylinders into spaceship
    else if(c == 'F'){
        catchRocketTubes();
        printf("[FILE] It's a F \n");
    }
    // Take a cylinder
    else if(c == 'P'){
        catchOneTube();
        printf("[FILE] It's a P \n");
    }
    // Store a cylinder
    else if(c == 'S'){
        switch(nbrCylindre){
            case 0:
                storeFirstTube();
                break;
            case 1:
                storeSecondTube();
                break;
            case 2:
                storeThirdTube();
                break;
            default:
                printf("[FILE] nbrCylindre store pb \n");
                break;
        }
        nbrCylindre++;       
        printf("[FILE] It's a S \n");
    }
    // Release a cylinder
    else if(c == 'D'){
        switch(nbrCylindre){
            case 3:
                putFirstTube();
                break;
            case 2:
                putSecondTube();
                break;
            case 1:
                putLastTube();
                break;
            default:
                printf("[FILE] nbrCylindre realpb \n");
                break;
        }
        nbrCylindre--;
        printf("[FILE] It's a D \n");
    }
    else if(c == '#'){}
    else if(c == '\n'){}
    else {
	if(c != 255)
            printf("[FILE] PARSING ERROR: %d\n", c);
        return 1;
    }
    return 0;
}
