#include "./headers/header.h"

// TODAS FUNÇÕES LIDAM COM APENAS UM PAD

/*
    ARG = ponteiro para UM pad, ponteiro para UM frame, ponteiro para UM level, UM caracter
    RET/MOD = sem modificações
    Controla o que deve ser realizado com pad, ou seja, testa se a tecla presionada é uma
        tecla que produz ação, realiza a verificação de colisão e desenha o pad no frame.
*/
void padControl(PADDLE *dummy_pad, BALL *dummy_ball, FRAME *frameGame, LEVEL *level, int ch){
    if(dummy_pad->botMode == FALSE){
        // Chama a função que realiza a troca na velocidade do pad
        padChVelocity(dummy_pad, KEY_LEFT, KEY_RIGHT, ch);
    }
    else{
        // Introduzindo erro aleatório
        if(randBinary(0.9)<level->errorProb)
            dummy_pad->velocity.x = 0;
        // Chama a função que configura bot
        else
            botDecisionControl(dummy_pad, dummy_ball, level);

    }
    // Chama a função que realiza verificação de choques
    padCollisionVerification(dummy_pad, frameGame);
    // Chama a função que escreve o pad no frame
    padDraw(dummy_pad, frameGame, dummy_pad->charCode);

}

/*
    ARG = ponteiro para UM pad
    RET/MOD = modifica as propriedades do pad
    Atualiza a posição do pad usando as velocidades correntes
*/
void padAttPos(PADDLE *dummy_pad){
    dummy_pad->position.x += dummy_pad->velocity.x;
    dummy_pad->position.y += dummy_pad->velocity.y;
}

/*
    ARG = ponteiro para UM pad
    RET/MOD = modifica as propriedades do pad
    Atualiza a posição do pad usando as velocidades correntes
*/
void padCollisionVerification(PADDLE *dummy_pad, FRAME *frameGame){
    int row, col;
    row = dummy_pad->position.y + dummy_pad->velocity.y;
    col = dummy_pad->position.x + dummy_pad->velocity.x;
    if(dummy_pad->vertical == FALSE){
        if(frameGame->src[dummy_pad->position.y][col] == LEFT_BLOCK)
            dummy_pad->velocity.x = 0;
        else if(frameGame->src[dummy_pad->position.y][col + dummy_pad->len-1] == RIGHT_BLOCK)
            dummy_pad->velocity.x = 0;
        else if(frameGame->src[dummy_pad->position.y][col + dummy_pad->len-1] == BARRIER_BLOCK)
            dummy_pad->velocity.x = 0;
        else if(frameGame->src[dummy_pad->position.y][col] == BARRIER_BLOCK)
            dummy_pad->velocity.x = 0;
    }
    else{
        if(frameGame->src[row][dummy_pad->position.x] == TOP_BLOCK)
            dummy_pad->velocity.y = 0;
        else if(frameGame->src[row + dummy_pad->len-1][dummy_pad->position.x] == BOT_BLOCK)
            dummy_pad->velocity.y = 0;
        else if(frameGame->src[row + dummy_pad->len-1][dummy_pad->position.x] == BARRIER_BLOCK)
            dummy_pad->velocity.y = 0;
        else if(frameGame->src[row][dummy_pad->position.x] == BARRIER_BLOCK)
            dummy_pad->velocity.y = 0;
    }
}
void padDraw(PADDLE *dummy_pad, FRAME *frameGame, int charCode){
    int i;
    if(dummy_pad->vertical == FALSE){
        for(i = 0; i < dummy_pad->len; i++)
            frameGame->src[dummy_pad->position.y][dummy_pad->position.x + i] = VOID_BLOCK;
        padAttPos(dummy_pad);
        for(i = 0; i < dummy_pad->len; i++)
            frameGame->src[dummy_pad->position.y][dummy_pad->position.x + i] = charCode;
    }
    else{
        for(i = 0; i < dummy_pad->len; i++)
            frameGame->src[dummy_pad->position.y + i][dummy_pad->position.x] = VOID_BLOCK;
        padAttPos(dummy_pad);
        for(i = 0; i < dummy_pad->len; i++)
            frameGame->src[dummy_pad->position.y + i][dummy_pad ->position.x] = charCode;
    }
}

int padKeyBoardControl(PADDLE* dummy_pad, int regressKey, int advanceKey, int ch){
    if(ch == regressKey)
        return -1;
    else if(ch == advanceKey)
        return 1;
    else
        return 0;
}
void padChVelocity(PADDLE* dummy_pad, int keyRegress, int keyAdvance, int ch){
    int velocity;
    if(dummy_pad->vertical == FALSE)
        dummy_pad->velocity.x = padKeyBoardControl(dummy_pad, dummy_pad->advanceKey, dummy_pad->regressKey, ch);
    else
        dummy_pad->velocity.y = padKeyBoardControl(dummy_pad, dummy_pad->advanceKey, dummy_pad->regressKey, ch);
}
