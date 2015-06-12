#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"
#include "macros.h"

// BALL
void ballControl(BALL*, PADDLE*,FRAME*, LEVEL*);
void ballAttPos(BALL*);
int ballCollisionVerification(BALL*, FRAME*);
void ballDraw(BALL*, FRAME *);
void ballAction(BALL*, PADDLE*, FRAME*, LEVEL*);
void ballAdd(BALL *, PADDLE *, LEVEL *);
void ballDel(BALL *, FRAME *, LEVEL *);
// PADDLE
void padAttPos(PADDLE*);
void padCollisionVerification(PADDLE*, FRAME*);
void padDraw(PADDLE*, FRAME*, int);
void padControl(PADDLE*, FRAME*, LEVEL*, int);
int padKeyBoardControl(PADDLE*, int, int, int);
void padChVelocity(PADDLE*, int, int, int);

// GRAPH
void frameDraw(WINDOW*, FRAME);
void configWindow();
void printMenu(WINDOW*, int, char**, int);
int configMenu();
WINDOW *create_newwin(int, int, int, int);
void waddchColor(WINDOW*, int, int);

// LEVEL
void loadMap(char barrerTable[MAP_HEIGHT][MAP_WIDTH], char*);
void cpMaptoFrame(FRAME*, LEVEL);
void loadLevel(LEVEL *level);

// CONFIG
void seedGen();
BOOL randBinary(float);
int randNumber(int);


#endif
