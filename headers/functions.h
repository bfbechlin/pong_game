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

//BOT
BALL testBallDistance(BALL*, PADDLE*);
void botDecisionControl(PADDLE*, BALL*, LEVEL*);
void controlBotPaddle(PADDLE*, BALL*, FRAME*, LEVEL*);

// GRAPH
void gameFrameDraw(WINDOW*, FRAME*);
void homeDraw(WINDOW *, FRAME *);
void configWindow();
void printMenu(WINDOW*, int, char**, int);
int configMenu(WINDOW*);
WINDOW *create_newwin(int, int, int, int);
void waddchColor(WINDOW*, int, int);
void scoreAtt(FRAME *, LEVEL *);
void newBallTimeAtt(FRAME *, FRAME *, int);
void blinkPlayer(WINDOW *, FRAME *, FRAME *, int);

/* FRAME*/
FRAME *create_newframe(int, int);
void delframe(FRAME *frame);
void frameDraw(WINDOW *, FRAME*, FRAME*);
void frameLoad(FRAME *, char *);
void frameAddNumber(FRAME *, int, int, int, int);
void frameAddString(FRAME *, char *, int, int);
void frameAddColor(FRAME *, int, int, int, int);


// LEVEL
void loadMap(char barrerTable[MAP_HEIGHT][MAP_WIDTH], char*);
void cpMaptoFrame(FRAME*, LEVEL*);
void loadLevel(LEVEL *);
void newLevel(LEVEL *, FRAME*, FRAME*, BALL*, PADDLE *);

// MODE
void PVPinitGame();
void CPUinitGame();

// CONFIG
void seedGen();
BOOL randBinary(float);
int randNumber(int);


#endif
