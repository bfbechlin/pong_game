#include "./headers/header.h"

int main(){
	int ch;
    char teste[15] = "maps/0.txt";
	BALL bal = {.position.x = 2*MAP_WIDTH/3, .position.y = MAP_HEIGHT-3, .velocity.x = 1, .velocity.y =-1, .enabled = TRUE};
    PADDLE pad = {.position.x = MAP_WIDTH/2, .position.y = MAP_HEIGHT-2, .velocity.x = 0, .velocity.y =0, .len = 15, .vertical = FALSE};
    LEVEL level = {.dificult = 1};
    loadMap(&level.map, teste); 

	sceneDraw(level);
	while((ch = getch()) != ESC) // Enquanto a tecla ESC nao for pressionada
    {
        padControl(&pad, level, ch);
    	ballControl(&bal, level);
        refresh(); //atualiza a tela
        usleep(1000000/30); //30 frames por segundo
    }
    endwin();
    return 0;
}
