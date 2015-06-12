#include "./headers/header.h"

/*
    ARG = ponteiro para UMA bola
    Atualiza posição da bola recebida.
*/
void ballAttPos(BALL *dummy_ball){
    dummy_ball->position.x += dummy_ball->velocity.x;
    dummy_ball->position.y += dummy_ball->velocity.y;
}

/*
    ARG = ponteiro para UMA bola, ponteiro para UM frame
    Verifica colisões com cenário e pads.
*/
int ballCollisionVerification(BALL *dummy_ball, FRAME *frameGame){
    int row, col;
    row = dummy_ball->position.y + dummy_ball->velocity.y;
    col = dummy_ball->position.x + dummy_ball->velocity.x;
    // BLOCOS DO FIM DO CENÁRIO
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
        if(frameGame->src[dummy_ball->position.y][col] >= PAD1H_BLOCK && frameGame->src[dummy_ball->position.y][col] <= BARRIER_BLOCK)
            dummy_ball->velocity.x *= -1;
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

/*
    ARG = ponteiro para UMA bola, ponteiro para UM frame
    Edita o frame com as novas posições das bolas, sendo necessário ter verificado as colisões
        e atualizado as velocidades da bola.
*/
void ballDraw(BALL *dummy_ball, FRAME *frameGame){
    if(dummy_ball->enabled == TRUE){
        // Apaga a posição onde a bola se encontrava anteriormente
        frameGame->src[dummy_ball->position.y][dummy_ball->position.x] = VOID_BLOCK;
        // Atualiza a posição da bola
        ballAttPos(dummy_ball); 
        // Desenha novamente a bola em sua nova posição
        frameGame->src[dummy_ball->position.y][dummy_ball->position.x] = BALL_BLOCK;
    }
}

/*
    ARG = ponteiro para UMA bola, ponteiro para VETOR pads, ponteiro para UM frame,
        ponteiro para UM level 
    Realiza todas a dinâmica de choques de UMA bola com objetos do cenário. Sendo assim
        também realiza a verificação do choque com pad e se estão com velocidades 
        contrárias
*/
void ballAction(BALL *dummy_ball, PADDLE *dummy_pad, FRAME *frameGame, LEVEL *level){
    int block; // Recebe a macro do pad, assim podendo identificar com qual ocorreu o choque
    switch(block = ballCollisionVerification(dummy_ball, frameGame)){
        case TOP_BLOCK:
            dummy_ball->velocity.y *= -1;
            // TEMPERÁRIO
            if(dummy_ball->position.x == 1 || dummy_ball->position.x == MAP_WIDTH-2)
                dummy_ball->velocity.x *= -1;
            break;
        case BOT_BLOCK:
            level->p1Score ++;
            ballDel(dummy_ball, frameGame, level);
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

/*
    ARG = ponteiro para VETOR bola, ponteiro para VETOR pads, ponteiro para UM frame,
        ponteiro para UM level 
    Realiza controle de TODAS as bolas, atualizando somente as que estão ativas.
*/
void ballControl(BALL *dummy_ball, PADDLE *dummy_pad, FRAME *frameGame, LEVEL *level){
	int i;
    // LEVANDO ARRAY DE BOLAS
    for(i = 0; i < MAXBALL; i++){
        if(dummy_ball[i].enabled == TRUE){
            ballAction(&dummy_ball[i], dummy_pad, frameGame, level);
            ballDraw(&dummy_ball[i], frameGame);
        }   
    }
}

void ballAdd(BALL *dummy_ball, PADDLE *dummy_pad, LEVEL *level){
    int index, i;
    BOOL found;  
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
    i = 0;
    do{
        if(dummy_ball[i].enabled == FALSE){
            dummy_ball[i] = ball;
            level->nBall += 1;
            found = TRUE;
        }
        i++;
    }while(found == FALSE && i < MAXBALL);
}
/*
    ARG = UMA BOLA
    Delata a bola
*/
void ballDel(BALL *dummy_ball, FRAME *frameGame, LEVEL *level){
    // Desativa bola
    dummy_ball->enabled = FALSE;
    // Apagando a bola da tela
    frameGame->src[dummy_ball->position.y][dummy_ball->position.x] = VOID_BLOCK;
    // Diminuindo a quantidade de bolas ativas
    level->nBall += -1;
}

void ballNewLevel(BALL *dummy_ball){
    int i;
    // Iniciando sem nenhuma bola
    for(i =0; i < MAXBALL; i++){
        dummy_ball[i].enabled = FALSE;
    }
}