#include "./headers/header.h"

/* testBallDistance recebe um array com as bolas em jogo, e a instancia de PADDLE do bot.
   Calcula a distancia entre todas as bolas e o pad e retorna a instancia de BALL mais proxima */
BALL testBallDistance(BALL *dummy_ball, PADDLE *botPad){
    int i=0;
    float distance, closerDist=80*80;
    BALL closerBall = {.position.x = (MAP_WIDTH/2), .position.y = (MAP_HEIGHT/2)}; //Atribui a closerBall uma bola imaginaria parada no centro do mapa

    if(botPad->vertical == FALSE){
        for(i=0; i < MAXBALL; i++){
            if(dummy_ball[i].enabled == TRUE && dummy_ball[i].velocity.y == -1){
                distance = (dummy_ball[i].position.x - (botPad->position.x + botPad->len/2))*(dummy_ball[i].position.x - (botPad->position.x + botPad->len/2)) + (dummy_ball[i].position.y - botPad->position.y)*(dummy_ball[i].position.y - botPad->position.y);
                if(distance < closerDist){
                    closerDist = distance;
                    closerBall = dummy_ball[i];
                }
            }
        }
    }
    else{
        for(i=0; i < MAXBALL; i++){
            if(dummy_ball[i].enabled == TRUE && dummy_ball[i].velocity.y == -1){
                distance = (dummy_ball[i].position.y - (botPad->position.y + botPad->len/2))*(dummy_ball[i].position.y - (botPad->position.y + botPad->len/2)) + (dummy_ball[i].position.x - botPad->position.x)*(dummy_ball[i].position.x - botPad->position.x);
                if(distance < closerDist){
                    closerDist = distance;
                    closerBall = dummy_ball[i];
                }
            }
        }
    }

    return closerBall;
}

/* botDecisionControl() recebe um PADDLE que será o bot, um array de BALL com as bolas em jogo, e um LEVEL, decide se o bot irá mover para esquerda ou direita comparando sua posição com a bola mais próxima */
void botDecisionControl(PADDLE *botPad, BALL *dummy_ball, LEVEL *level){
    BALL closerBall;

    if(botPad->botMode == TRUE){
        closerBall = testBallDistance(dummy_ball, botPad);

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
