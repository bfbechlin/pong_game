#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"
#include "macros.h"

// BALL
void ballControl(BALL*, PADDLE*,FRAME*, LEVEL*);
void ballAttPos(BALL*);
int ballCollisionVerification(BALL*, FRAME*);
void ballDraw(BALL*, FRAME *);

// PADDLE
void padAttPos(PADDLE*);
void padCollisionVerification(PADDLE*, FRAME*);
void padDraw(PADDLE*, FRAME*, int);
void padControl(PADDLE*, FRAME*, LEVEL*, int);
int padKeyBoardControl(PADDLE*, int, int, int);
void padChVelocity(PADDLE*, int, int, int);

// GRAPH
void frameDraw(FRAME);
void setCursor(int, int);
void configWindow();

// LEVEL
void loadMap(int barrerTable[MAP_HEIGHT][MAP_WIDTH], char*);
void cpMaptoFrame(FRAME*, LEVEL);
#endif