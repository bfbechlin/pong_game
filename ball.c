#include "./headers/header.h"

void ballAttPos(BALL *dummy_ball){
    dummy_ball->position.x += dummy_ball->velocity.x;
    dummy_ball->position.y += dummy_ball->velocity.y;
}

int ballCollisionVerification(BALL *dummy_ball, FRAME *frameGame){

    // FUNÇÃO DIFERENTE
    int row, col;
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
        return frameGame->src[row][dummy_ball->position.x];
    }
    // VERIFICANDO COLISÃO COM BARREIRAS E PADS
    if(frameGame->src[dummy_ball->position.y][col] >= PAD1H_BLOCK && frameGame->src[dummy_ball->position.y][col] <= BARRIER_BLOCK){
        dummy_ball->velocity.x *= -1;
        return frameGame->src[dummy_ball->position.y][col];
    }
    // COLISÕES DIAGONAIS COM BARREIRAS E PADS
    if(frameGame->src[row][col] >= PAD1H_BLOCK && frameGame->src[row][col] <= BARRIER_BLOCK){
        dummy_ball->velocity.y *= -1;
        dummy_ball->velocity.x *= -1;
        return FALSE;
    }
}

void ballDraw(BALL *dummy_ball, FRAME *frameGame){
    frameGame->src[dummy_ball->position.y][dummy_ball->position.x] = VOID_BLOCK;
    ballAttPos(dummy_ball); // Atualiza a posição da bola
    frameGame->src[dummy_ball->position.y][dummy_ball->position.x] = BALL_BLOCK;
}

void ballAction(BALL *dummy_ball, PADDLE *dummy_pad, FRAME *frameGame, LEVEL *level){
    int block; // Recebe a macro do pad, assim podendo identificar com qual ocorreu o choque
    switch(block = ballCollisionVerification(dummy_ball, frameGame)){
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
        // CHOQUES COM PADS HORIZONTAIS
        case PAD1H_BLOCK:
        case PAD2H_BLOCK:
            if((dummy_pad[block-1].velocity.x * -1) == dummy_ball->velocity.x)
                dummy_ball->velocity.x *= -1; 
            break;
        // CHOQUES COM PADS VERTICAIS
        case PAD1V_BLOCK:
        case PAD2V_BLOCK:
            if((dummy_pad[block-1].velocity.y*-1) == dummy_ball->velocity.y)
                dummy_ball->velocity.y*=-1; 
            break;
        default:
            break;
    }
}

void ballControl(BALL *dummy_ball, PADDLE *dummy_pad, FRAME *frameGame, LEVEL *level){
	int i;
    // LEVANDO ARRAY DE BOLAS
    for(i = 0; i < level->nBall; i++){
        ballAction(&dummy_ball[i], dummy_pad, frameGame, level);
        ballDraw(&dummy_ball[i], frameGame);   
    }
}

void ballAttArray(BALL *dummy_ball, LEVEL *level){
    int i, j;
    BOOL change;
    for(i = MAXBALL; i >= 0  ; i--){
        if(dummy_ball[i].enabled == TRUE && i >= level->nBall){
            change = TRUE;
            j = i;
            while(change && j >= 0){
                if(dummy_ball[j].enabled == FALSE){
                    dummy_ball[j] = dummy_ball[i];
                    change = FALSE;
                }
                j--;
            }
        }
    }
}

void ballAdd(BALL *dummy_ball, PADDLE *dummy_pad, LEVEL *level){
    int index;  
    BALL ball;
    // Definindo velocidades aleatóriamente como 1 e -1
    ball.velocity.x = randBinary(0.5)*2 - 1;
    ball.velocity.y = randBinary(0.5)*2 - 1;
    // Ativando a bola
    ball.enabled = TRUE;
    // Definindo posição inicial através das posições dos pads
    switch(index = randNumber(level->nPad)){
        //PAD SUPERIOR
        case 1:
            ball.position.y = dummy_pad[index - 1].position.y + 1;
            ball.position.x = dummy_pad[index - 1].position.x + dummy_pad[index - 1].len/2;
            ball.velocity.y = 1;
            break;
        //PAD INFERIOR
        case 2:
            ball.position.y = dummy_pad[index - 1].position.y - 1;
            ball.position.x = dummy_pad[index - 1].position.x + dummy_pad[index - 1].len/2;
            ball.velocity.y = -1;
            break;
        //PAD LATERAL DIREITO
        case 3:
            ball.position.x = dummy_pad[index - 1].position.x + 1;
            ball.position.y = dummy_pad[index - 1].position.y + dummy_pad[index - 1].len/2;
            ball.velocity.x = 1;
            break;
        //PAD LATERAL ESQUERDO
        case 4:
            ball.position.x = dummy_pad[index - 1].position.x - 1;
            ball.position.y = dummy_pad[index - 1].position.y + dummy_pad[index - 1].len/2;
            ball.velocity.x = -1;
            break;
    }
    
    // Adicionando bola na próxima posição disponível
    dummy_ball[level->nBall] = ball;
    level->nBall += 1;
}

void ballDel(BALL *dummy_ball, PADDLE *dummy_pad, LEVEL *level){
    // Desativa bola
    dummy_ball->enabled = FALSE;
    // Organizando o array de bolas
    ballAttArray(dummy_ball, level);
    level->nBall += -1;
}

void ballNewLevel(BALL *dummy_ball){
    int i;
    // Iniciando sem nenhuma bola
    for(i =0; i < MAXBALL; i++){
        dummy_ball[i].enabled = FALSE;
    }
}