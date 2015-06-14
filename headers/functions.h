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
void gameFrameDraw(WINDOW*, FRAME*);
void configWindow();
void printMenu(WINDOW*, int, char**, int);
int configMenu(WINDOW*);
WINDOW *create_newwin(int, int, int, int);
void waddchColor(WINDOW*, int, int);

void testeBallTime(FRAME *, int);
void statsFrameDraw(WINDOW *, FRAME*, FRAME*);
/* FRAME*/
FRAME* create_newframe(int, int);
void frameLoad(FRAME *, char *);
void frameAddNumber(FRAME *, int, int, int, int);
void frameAddString(FRAME *, char *, int, int);

// LEVEL
void loadMap(char barrerTable[MAP_HEIGHT][MAP_WIDTH], char*);
void cpMaptoFrame(FRAME*, LEVEL);
void loadLevel(LEVEL *level);

// CONFIG
void seedGen();
BOOL randBinary(float);
int randNumber(int);


#endif
