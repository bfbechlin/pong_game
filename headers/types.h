#ifndef TYPES_H
#define TYPES_H

#include "macros.h"

// **TIPOS**

typedef unsigned char BOOL;

// **ESTRUTURAS**

typedef struct
{
    int x;
    int y;

}COORD;

typedef struct{

    COORD position;
    COORD velocity;
    BOOL enabled;

}BALL;

typedef struct{

    COORD position;
    COORD velocity;

    unsigned int len;

    char charCode;

    BOOL botMode;
    BOOL vertical;

    int advanceKey;
    int regressKey;

    int speed;

}PADDLE;

typedef struct{

    char map[MAP_HEIGHT][MAP_WIDTH];
    char mapCode;
    int dificult;
    float errorProb;
    int mode;

    int nPad;
    int nBall;
    int newBallTime;
    int newBallCurrentTime;

    int p1Score;
    int p2Score;

}LEVEL;

typedef struct{

    char **src;
    int width;
    int height;

}FRAME;

typedef struct{

    char playerName[NAME_LEN];
    int recordLevel;

}RECORD;

#endif
