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

    BOOL vertical;
}PADDLE;

typedef struct{
    int map[MAP_HEIGHT][MAP_WIDTH];
    int dificult;
    int mode;
}LEVEL;

typedef struct{
    int src[MAP_HEIGHT][MAP_WIDTH];
    int width;
    int height;
}FRAME;
#endif