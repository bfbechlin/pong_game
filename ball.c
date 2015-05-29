#include "./headers/header.h"

void ballAttPos(BALL *dummy_ball){
    dummy_ball->position.x += dummy_ball->velocity.x;
    dummy_ball->position.y += dummy_ball->velocity.y;
}
int ballCollisionVerification(BALL *dummy_ball, FRAME *frameGame){
    int row, col;
    BOOL collisionTest = FALSE;
    row = dummy_ball->position.y + dummy_ball->velocity.y;
    col = dummy_ball->position.x + dummy_ball->velocity.x;
    if(frameGame->src[row][col] == TOP_BLOCK)
        return TOP_BLOCK;
    if(frameGame->src[row][col] == BOT_BLOCK)
        return BOT_BLOCK;
    if(frameGame->src[row][col] == LEFT_BLOCK)
        return LEFT_BLOCK;
    if(frameGame->src[row][col] == RIGHT_BLOCK)
        return RIGHT_BLOCK;
    // VERIFICANDO COLISÃO COM BARREIRAS E PADS
    if(frameGame->src[row][dummy_ball->position.x] >= PAD1H_BLOCK && frameGame->src[row][dummy_ball->position.x] <= BARRIER_BLOCK){
        dummy_ball->velocity.y *= -1;
        collisionTest = TRUE;
    }
    // VERIFICANDO COLISÃO COM BARREIRAS E PADS
    if(frameGame->src[dummy_ball->position.y][col] >= PAD1H_BLOCK && frameGame->src[dummy_ball->position.y][col] <= BARRIER_BLOCK){
        dummy_ball->velocity.x *= -1;
        collisionTest = TRUE;
    }
    // COLISÕES DIAGONAIS COM BARREIRAS E PADS
    if(frameGame->src[row][col] >= PAD1H_BLOCK && frameGame->src[row][col] <= BARRIER_BLOCK){
        if(collisionTest == FALSE){
            dummy_ball->velocity.y *= -1;
            dummy_ball->velocity.x *= -1;
        }
    }
    return 0;
}
void ballDraw(BALL *dummy_ball, FRAME *frameGame){
    frameGame->src[dummy_ball->position.y][dummy_ball->position.x] = VOID_BLOCK;
    ballAttPos(dummy_ball); // Atualiza a posição da bola
    frameGame->src[dummy_ball->position.y][dummy_ball->position.x] = BALL_BLOCK;
}
void ballControl(BALL *dummy_ball, FRAME *frameGame, LEVEL level){
	// verifica colisoes
    switch(ballCollisionVerification(dummy_ball, frameGame)){
        case TOP_BLOCK:
        case BOT_BLOCK:
            dummy_ball->velocity.y *= -1;
            // TEMPERÁRIO
            if(dummy_ball->position.x == 1 || dummy_ball->position.x == MAP_WIDTH-2)
                dummy_ball->velocity.x *= -1;
            break;
        case RIGHT_BLOCK:
        case LEFT_BLOCK:
            dummy_ball->velocity.x *= -1;
            break;
        default:
            break;
    }
    // desenha e movimenta a bola
    ballDraw(dummy_ball, frameGame);	
}
void setVelOnCollision(PADDLE dummy_pad, BALL dummy_ball, LEVEL level){

}