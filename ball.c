#include <curses.h>
#include "./headers/types.h"
#include "./headers/macros.h"
#include "./headers/functions.h"

void ballAttPos(BALL* dummy_ball){
    dummy_ball->position.x += dummy_ball->velocity.x;
    dummy_ball->position.y += dummy_ball->velocity.y;
}
int ballCollisionVerification(BALL* dummy_ball, LEVEL level){
    int row, col;
    BOOL collsionTest = FALSE;
    row = dummy_ball->position.y + dummy_ball->velocity.y;
    col = dummy_ball->position.x + dummy_ball->velocity.x;
    /*
    if(level.map[row][col] == 1)
        return 1;
    if(level.map[row][col] == 2)
        return 2;
    */
    if(level.map[row][dummy_ball->position.x] != 0){
        dummy_ball->velocity.y *= -1;
        collsionTest = TRUE;
    }
    if(level.map[dummy_ball->position.y][col] != 0){
        dummy_ball->velocity.x *= -1;
        collsionTest = TRUE;
    }
    if(level.map[row][col] == 5){
        if(collsionTest == FALSE){
            dummy_ball->velocity.y *= -1;
            dummy_ball->velocity.x *= -1;
        }
    }
    return 6;
}
void ballDraw(BALL* dummy_ball, LEVEL level){
    setCursor(dummy_ball->position); // altera a posicao do cursor para o da bola
    printw(" "); // imprime um espaco sobre a bola
    ballAttPos(dummy_ball); // Atualiza a posição da bola
    setCursor(dummy_ball->position); //altera a posicao do cursor paraa nova posica da bola
    printw("%d", level.map[dummy_ball->position.y + dummy_ball->velocity.y][dummy_ball->position.x+ dummy_ball->velocity.x]); //imprime a bola
}
void ballControl(BALL* dummy_ball, LEVEL level){
	// verifica colisoes
    switch(ballCollisionVerification(dummy_ball, level)){
        case 1:
        case 2:
            dummy_ball->velocity.y *= -1;
            break;
        default:
            break;
    }
    // desenha e movimenta a bola
    ballDraw(dummy_ball, level);	
}
