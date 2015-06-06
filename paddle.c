#include "./headers/header.h"

void padAttPos(PADDLE *dummy_pad){
    dummy_pad->position.x += dummy_pad->velocity.x;
    dummy_pad->position.y += dummy_pad->velocity.y;
}
void padCollisionVerification(PADDLE *dummy_pad, FRAME *frameGame){
    int row, col;
    row = dummy_pad->position.y + dummy_pad->velocity.y;
    col = dummy_pad->position.x + dummy_pad->velocity.x;

    if(frameGame->src[row][dummy_pad->position.x] == TOP_BLOCK){
        dummy_pad->velocity.y = 0;
    }
    else if(frameGame->src[row + dummy_pad->len-1][dummy_pad->position.x] == BOT_BLOCK){
        dummy_pad->velocity.y = 0;
    }

    if(frameGame->src[dummy_pad->position.y][col] == LEFT_BLOCK){
        dummy_pad->velocity.x = 0;
    }
    else if(frameGame->src[dummy_pad->position.y][col + dummy_pad->len-1] == RIGHT_BLOCK){
        dummy_pad->velocity.x = 0;
    }
}
void padDraw(PADDLE *dummy_pad, FRAME *frameGame, int charCode){
    int i;
    
    if(dummy_pad->vertical == FALSE){
        for(i = 0; i < dummy_pad->len; i++){
            frameGame->src[dummy_pad->position.y][dummy_pad->position.x + i] = VOID_BLOCK;
        }
        padAttPos(dummy_pad);
        for(i = 0; i < dummy_pad->len; i++){
            frameGame->src[dummy_pad->position.y][dummy_pad->position.x + i] = charCode;
        }
    }
    else{
        for(i = 0; i < dummy_pad->len; i++){
            frameGame->src[dummy_pad->position.y + i][dummy_pad->position.x] = VOID_BLOCK;
        }
        padAttPos(dummy_pad);
        for(i = 0; i < dummy_pad->len; i++){
            frameGame->src[dummy_pad->position.y + i][dummy_pad ->position.x] = charCode;
        }
    }
}
void padControl(PADDLE *dummy_pad, FRAME *frameGame, LEVEL *level, int ch){

    padChVelocity(dummy_pad, KEY_LEFT, KEY_RIGHT, ch);
    padCollisionVerification(dummy_pad, frameGame);
    padDraw(dummy_pad, frameGame, PAD1H_BLOCK);    
}
int padKeyBoardControl(PADDLE* dummy_pad, int keyRegress, int keyAdvance, int ch){
    if(ch == keyRegress)
        return -1;
    else if(ch == keyAdvance)
        return 1;
    else
        return 0;
}
void padChVelocity(PADDLE* dummy_pad, int keyRegress, int keyAdvance, int ch){
    int velocity;
    if(dummy_pad->vertical == FALSE){
        dummy_pad->velocity.x = padKeyBoardControl(dummy_pad, KEY_LEFT, KEY_RIGHT, ch);
            
    }
    else{
        dummy_pad->velocity.y = padKeyBoardControl(dummy_pad, KEY_LEFT, KEY_RIGHT, ch);
    }
}
