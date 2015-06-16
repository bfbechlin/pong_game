#include "./headers/header.h"
#include <math.h>

/* countReturningBalls recebe um array de BALL com as bolas em jogo, e uma instancia de level. Le o array inteiro e conta quantas bolas estao avançando em direção ao bot.
   Retorna um inteiro com o valor de bolas indo até o bot */
int countReturningBalls(BALL *dummy_ball, LEVEL *level){
    int i;
    int numReturningBalls=0;
    
    for(i=0; i< level->nBall; i++){
        if(dummy_ball[i].enabled == TRUE && dummy_ball[i].velocity.y == -1)
            numReturningBalls++;
    }
    return numReturningBalls;
}

/* Funcao testBallsDirection recebe um array com as bolas em jogo, um array onde ira salvar as bolas indo na direção do bot, e um level. 
   Faz a leitura de todas as bolas e guarda as bolas que estão indo em direção ao Bot no segundo array*/ 
void testBallsDirection(BALL *dummy_ball, BALL *returningBalls, LEVEL *level){
    int i, j=0;
    
    for(i=0; i < level->nBall; i++){
        if(dummy_ball[i].enabled == TRUE && dummy_ball[i].velocity.y == -1){ //testa se a i-esima bola está ativada e vai em direção ao bot
            returningBalls[j] = dummy_ball[i]; //salva em returningBalls somente as bolas ativadas que estao indo até o bot
            j++;
        }
    }
}

/* testBallDistance recebe um array com as bolas retornando em direção ao bot, o numero de bolas retornando, e a instancia de PADDLE do bot.
   Calcula a distancia entre todas as bolas e o pad e retorna a instancia de BALL mais proxima */ 
BALL testBallDistance(BALL *returningBalls, int numReturningBalls, PADDLE *botPad){
    int i=0;
    float distance, closerDist;
    BALL closerBall = returningBalls[i]; //Atribui a closerBall o valor da primeira bola para iniciar os testes
    
    /* Calcula distancia entre returningBall[0] e botPad usando pitagoras e salva como closerDist temporoario */
    closerDist = sqrt((returningBalls[i].position.x - (botPad->position.x + botPad->len/2))*(returningBalls[i].position.x - (botPad->position.x + botPad->len/2)) + (returningBalls[i].position.y - botPad->position.y)*(returningBalls[i].position.y - botPad->position.x));
    
    if(botPad->vertical == FALSE){
        for(i=1; i < numReturningBalls; i++){
            distance = sqrt((returningBalls[i].position.x - (botPad->position.x + botPad->len/2))*(returningBalls[i].position.x - (botPad->position.x + botPad->len/2)) + (returningBalls[i].position.y - botPad->position.y)*(returningBalls[i].position.y - botPad->position.y));
            if(distance < closerDist){
                closerDist = distance;
                closerBall = returningBalls[i];
            }
        }
    }
    else{
        for(i=1; i < numReturningBalls; i++){
            distance = sqrt((returningBalls[i].position.y - (botPad->position.y + botPad->len/2))*(returningBalls[i].position.y - (botPad->position.y + botPad->len/2)) + (returningBalls[i].position.x - botPad->position.x)*(returningBalls[i].position.x - botPad->position.x));
            if(distance < closerDist){
                closerDist = distance;
                closerBall = returningBalls[i];
            }
        }
    }

    return closerBall;
}

/* botDecisionControl() recebe um PADDLE que será o bot, um array de BALL com as bolas em jogo, e um LEVEL, decide se o bot irá mover para esquerda ou direita comparando sua posição com a bola mais próxima */
void botDecisionControl(PADDLE *botPad, BALL *dummy_ball, LEVEL *level, int numRetBalls){
    int numReturningBalls = numRetBalls;
    BALL closerBall;
    BALL returningBalls[numReturningBalls];

    testBallsDirection(dummy_ball, returningBalls, level);

    if(botPad->botMode == TRUE){
        closerBall = testBallDistance(returningBalls, numReturningBalls, botPad);
        
        if(botPad->vertical == FALSE){
            if((botPad->position.x + botPad->len/2) > closerBall.position.x)
                botPad->velocity.x = -1; //botPad está mais a direita da bola, então deve andar para esquerda(-1)
            else if((botPad->position.x + botPad->len/2) < closerBall.position.x)
                botPad->velocity.x = 1; //botPad está mais a esquerda da bola, então deve andar para direita(1)
            else
                botPad->velocity.x = 0; //botPad está alinhado com a bola, então deve ficar parado(0)
        }
    }
        else{
            if((botPad->position.y + botPad->len/2) > closerBall.position.y)
                botPad->velocity.y = -1; //botPad está mais a direita da bola, então deve andar para esquerda(-1)
            else if((botPad->position.y + botPad->len/2) < closerBall.position.y)
                botPad->velocity.y = 1; //botPad está mais a esquerda da bola, então deve andar para direita(1)
            else
                botPad->velocity.y = 0; //botPad está alinhado com a bola, então deve ficar parado(0)
        }
} 
/* controlBotPaddle() recebe um PADDLE que será o bot, um array de BALL com as bolas em jogo, um FRAME e um LEVEL, 
   e controla a movimentação do bot, verifica as colisões e desenha o pad na nova posição */
void controlBotPaddle(PADDLE *botPad, BALL *dummy_ball,  FRAME *frameGame, LEVEL *level){
    int numRetBalls;
    if((numRetBalls = countReturningBalls(dummy_ball, level)) > 0){
        botDecisionControl(botPad, dummy_ball, level, numRetBalls);
        padCollisionVerification(botPad, frameGame);
        padDraw(botPad, frameGame, botPad->charCode);
    }
}
