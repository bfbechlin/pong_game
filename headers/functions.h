#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"
#include "macros.h"

// BALL
void ballControl(BALL*, LEVEL);
void ballAttPos(BALL*);
int ballCollisionVerification(BALL*, LEVEL);
void ballDraw(BALL*, LEVEL);

// PADDLE
void padAttPos(PADDLE*);
void padCollisionVerification(PADDLE*, LEVEL);
void padDraw(PADDLE*, LEVEL);
void padControl(PADDLE*, LEVEL, int);
int padKeyBoardControl(PADDLE*, int, int, int);

// GRAPH
void setCursor(int, int);
void sceneDraw(LEVEL);

// LEVEL
void loadMap(int barrerTable[MAP_HEIGHT][MAP_WIDTH], char*);
#endif