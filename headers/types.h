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
    // Posições relacionadas com a primeira posição de um array
    COORD position;
    COORD velocity;
    BOOL enabled;
}BALL;

typedef struct{
    // Posições relacionadas com a primeira posição de um array
    COORD position;
    // Velocidades X e Y
    COORD velocity;
    // Tamanho da plataforma
    unsigned int len;
    BOOL vertical;
    char printPad[MAP_HEIGHT/2];
    int color;

}PADDLE;

typedef struct{
    int map[MAP_HEIGHT][MAP_WIDTH];
    int dificult;
    int mode;
}LEVEL;

#endif