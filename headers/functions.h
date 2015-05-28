#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "macros.h"

// BALL
void ballControl(BALL*, LEVEL);
void ballAttPos(BALL*);
int ballCollisionVerification(BALL*, LEVEL);
void ballDraw(BALL*, LEVEL);


// GRAPH
void setCursor(COORD);
void sceneDraw(LEVEL);

// LEVEL
void loadMap(int barrerTable[GAME_HEIGHT][GAME_WIDTH], char*);
#endif