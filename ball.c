#include <curses.h>
#include "./headers/types.h"
#include "./headers/macros.h"
#include "./headers/functions.h"

void ballAttPos(BALL* dummy_ball){
    dummy_ball->position.x += dummy_ball->velocity.x;
    dummy_ball->position.y += dummy_ball->velocity.y;
}
void ballCollisionVerificationScene(BALL* dummy_ball){
    if(dummy_ball->position.x + dummy_ball->velocity.x == 0 || dummy_ball->position.x + dummy_ball->velocity.x == WIDTH-1) 
        dummy_ball->velocity.x*=-1;

    if(dummy_ball->position.y + dummy_ball->velocity.y == 0 || dummy_ball->position.y + dummy_ball->velocity.y == HEIGHT-1) 
        dummy_ball->velocity.y*=-1;
}
void ballDraw(BALL* dummy_ball){
    setCursor(dummy_ball->position); // altera a posicao do cursor para o da bola
    printw(" "); // imprime um espaco sobre a bola
    ballAttPos(dummy_ball); // Atualiza a posição da bola
    setCursor(dummy_ball->position); //altera a posicao do cursor paraa nova posica da bola
    printw("O"); //imprime a bola
}
void ballControl(BALL* dummy_ball){
	// verifica colisoes
    ballCollisionVerificationScene(dummy_ball);
    // desenha e movimenta a bola
    ballDraw(dummy_ball);	
}
