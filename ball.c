#include "./headers/header.h"

// FUNÇÕES QUE LIDAM COM TODAS AS BOLAS

/*
    ARG = ponteiro para VETOR bola
    RET/MOD = modifica a propriedade das bolas
    Deixa todas as bolas desativadas usado para início da fase
*/
void ballNewLevel(BALL *dummy_ball){
    int i;
    // Iniciando sem nenhuma bola
    for(i =0; i < MAXBALL; i++){
        dummy_ball[i].enabled = FALSE;
    }
}

/*
    ARG = ponteiro para VETOR bola, ponteiro para VETOR pads, ponteiro para UM frame,
        ponteiro para UM level
    RET /
    Realiza controle de TODAS as bolas, atualizando somente as que estão ativas.
*/
void ballControl(BALL *dummy_ball, PADDLE *dummy_pad, FRAME *frameGame, LEVEL *level){
    int i;
    // Enviando o array de bolas
    for(i = 0; i < MAXBALL; i++){
        if(dummy_ball[i].enabled == TRUE){
            ballAction(&dummy_ball[i], dummy_pad, frameGame, level);
            ballDraw(&dummy_ball[i], frameGame);
        }
    }
}

/*
    ARG = ponteiro para VETOR bola, ponteiro para VETOR pads, ponteiro para UM level
    Adiciona uma bola no array no indice mais próxima do zero e que esteja desativada.
    A posição dessa bola é em cima de algum dos pads, aleatório, e sua direção também
        é aletória.
*/
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
            // Copiando a struct da bola local para as bolas do jogo
            dummy_ball[i] = ball;
            level->nBall += 1;
            found = TRUE;
        }
        i++;
    }while(found == FALSE && i < MAXBALL);
}

// FUNÇÕES QUE LIDAM SOMENTE COM UMA BOLA

/*
    ARG = ponteiro para UMA bola, ponteiro para UM frame, ponteiro para UM level
    Delata já apaga a bola recebida da tela
*/
void ballDel(BALL *dummy_ball, FRAME *frameGame, LEVEL *level){
    // Desativa bola
    dummy_ball->enabled = FALSE;
    // Apagando a bola da tela
    frameGame->src[dummy_ball->position.y][dummy_ball->position.x] = VOID_BLOCK;
    // Diminuindo a quantidade de bolas ativas
    level->nBall --;
    if(level->nBall == 0)
        level->newBallCurrentTime = 2;
}

/*
    ARG = ponteiro para UMA bola, ponteiro para UM frame            XX
    Verifica colisões com cenário e pads.                           OX
    Da seguinte forma, considerando a bola na digonal com velocidade positivas


*/
int ballCollisionVerification(BALL *dummy_ball, FRAME *frameGame){
    int block;

    if((block = frameGame->src[dummy_ball->position.y + dummy_ball->velocity.y]
    [dummy_ball->position.x]) > BALL_BLOCK){
        dummy_ball->velocity.y *= -1;
        // TESTANDO COLISÃO LATERAL DUPLA
        if(frameGame->src[dummy_ball->position.y]
        [dummy_ball->position.x + dummy_ball->velocity.x] > BALL_BLOCK){
            dummy_ball->velocity.x *= -1;
            // Cuidar que as velocidades já foram atualizadas então deve-se diminuir
            //  para ter o efeito de somar as velocidades anteriores. Assim, é possível
            //  encontrar o block diagonal onde houve a colisão
            block = frameGame->src[dummy_ball->position.y - dummy_ball->velocity.y]
            [dummy_ball->position.x - dummy_ball->velocity.x];
            return block;
        }
        return block;
    }

    if((block = frameGame->src[dummy_ball->position.y]
    [dummy_ball->position.x + dummy_ball->velocity.x]) > BALL_BLOCK){
        dummy_ball->velocity.x *= -1;
        return block;
    }
    if((block = frameGame->src[dummy_ball->position.y + dummy_ball->velocity.y][dummy_ball->position.x + dummy_ball->velocity.x]) > BALL_BLOCK){
        dummy_ball->velocity.x *= -1;
        dummy_ball->velocity.y *= -1;
        return block;
    }
    return FALSE;
}

/*
    ARG = ponteiro para UMA bola, ponteiro para VETOR pads, ponteiro para UM frame,
        ponteiro para UM level
    Realiza todas a dinâmica de choques de UMA bola com objetos do cenário. Sendo assim
        também realiza a verificação do choque com pad e se estão com velocidades
        contrárias. Também realiza teste se o modo de é com 4 pads.
*/
void ballAction(BALL *dummy_ball, PADDLE *dummy_pad, FRAME *frameGame, LEVEL *level){
    int index; // Recebe a macro do pad, assim podendo identificar com qual ocorreu o choque
    switch(index = ballCollisionVerification(dummy_ball, frameGame)){
        case TOP_BLOCK:
            level->p1Score --;
            ballDel(dummy_ball, frameGame, level);
            break;
        case BOT_BLOCK:
            level->p2Score --;
            ballDel(dummy_ball, frameGame, level);
            break;
         case LEFT_BLOCK:
            if(level->mode > PvsP){
                level->p1Score --;
                ballDel(dummy_ball, frameGame, level);
            }
            break;
        case RIGHT_BLOCK:
            if(level->mode > PvsP){
                level->p2Score --;
                ballDel(dummy_ball, frameGame, level);
            }
            break;
        // CHOQUES COM PADS HORIZONTAIS
        case PAD1H_BLOCK:
        case PAD2H_BLOCK:
            if((dummy_pad[index - SHIFT_PAD].velocity.x * -1) == dummy_ball->velocity.x)
                dummy_ball->velocity.x *= -1;
            break;
        // CHOQUES COM PADS VERTICAIS
        case PAD1V_BLOCK:
        case PAD2V_BLOCK:
            if((dummy_pad[index - SHIFT_PAD].velocity.y*-1) == dummy_ball->velocity.y)
                dummy_ball->velocity.y*=-1;
            break;
        default:
            break;
    }
}

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
