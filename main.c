#include <stdlib.h>
#include <curses.h>
#include "./headers/types.h"
#include "./headers/macros.h"
#include "./headers/functions.h"

int main(){
	int ch;
    char teste[15] = "maps/0.txt";
	BALL b = {.position.x = 2*WIDTH/3, .position.y = HEIGHT-2, .velocity.x = 1, .velocity.y =-1, .enabled = TRUE};
    LEVEL l = {.dificult = 1};
    loadMap(&l.map, teste); 

    int i,j;
    for(i = 0; i < GAME_HEIGHT; i ++){
        for(j = 0; j < GAME_WIDTH; j ++){
            printf("%d",l.map[i][j]);
        }
        printf("\n");
    }    
    getchar();

	sceneDraw(l);
	while((ch = getch()) != ESC) // Enquanto a tecla ESC nao for pressionada
    {

    	ballControl(&b, l);
        refresh(); //atualiza a tela
        usleep(1000000/30); //30 frames por segundo
    }
    endwin();
    return 0;
}
