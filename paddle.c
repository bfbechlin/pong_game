#include "./headers/header.h"

void padAttPos(PADDLE* dummy_pad){
    dummy_pad->position.x += dummy_pad->velocity.x;
    dummy_pad->position.y += dummy_pad->velocity.y;
}
void padCollisionVerification(PADDLE* dummy_pad, LEVEL level){
    int row, col;
    row = dummy_pad->position.y + dummy_pad->velocity.y;
    col = dummy_pad->position.x + dummy_pad->velocity.x;

    if(level.map[row][dummy_pad->position.x] != 0){
        dummy_pad->velocity.y = 0;
    }
    else if(level.map[row + dummy_pad->len-1][dummy_pad->position.x] != 0){
        dummy_pad->velocity.y = 0;
    }

    if(level.map[dummy_pad->position.y][col] != 0){
        dummy_pad->velocity.x = 0;
    }
    else if(level.map[dummy_pad->position.y][col + dummy_pad->len-1] != 0){
        dummy_pad->velocity.x = 0;
    }
}
void padDraw(PADDLE* dummy_pad, LEVEL level){
    int i;

    if(dummy_pad->vertical == FALSE){
        setCursor(dummy_pad->position.y, dummy_pad->position.x);
        attron(COLOR_PAIR(1));
        for(i = 0; i < dummy_pad->len; i++){
            addch(' ');
        }
        attroff(COLOR_PAIR(1));
        padAttPos(dummy_pad);
        setCursor(dummy_pad->position.y, dummy_pad->position.x);
        attron(COLOR_PAIR(4));
        for(i = 0; i < dummy_pad->len; i++){
            addch(ACS_CKBOARD);
        }
        attroff(COLOR_PAIR(4));
    }
    else{
        attron(COLOR_PAIR(1));
        for(i = 0; i < dummy_pad->len; i++){
            setCursor(dummy_pad->position.y + i, dummy_pad->position.x);
            addch(' ');
        }
        attroff(COLOR_PAIR(1));
        padAttPos(dummy_pad);
        setCursor(dummy_pad->position.y, dummy_pad->position.x);
        attron(COLOR_PAIR(4));
        for(i = 0; i < dummy_pad->len; i++){
            addch(176);
        }
        attroff(COLOR_PAIR(4));
    }
}
void padControl(PADDLE* dummy_pad, LEVEL level, int ch){

    dummy_pad->velocity.x = padKeyBoardControl(dummy_pad, KEY_LEFT, KEY_RIGHT, ch);
    padCollisionVerification(dummy_pad, level);
    padDraw(dummy_pad, level);    
}
int padKeyBoardControl(PADDLE* dummy_pad, int keyRegress, int keyAdvance, int ch){
    if(ch == keyRegress)
        return -1;
    else if(ch == keyAdvance)
        return 1;
    else
        return 0;
}