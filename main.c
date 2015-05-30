#include "./headers/header.h"

int main(){
    long unsigned int millis;
	int ch = -1;
    char map[10] = "maps/0.txt";
	millis = 0;
    BALL ball = {.position.x = 2*MAP_WIDTH/3, .position.y = MAP_HEIGHT-3, .velocity.x = 1, .velocity.y =-1, .enabled = TRUE};
    PADDLE pad = {.position.x = MAP_WIDTH/2, .position.y = MAP_HEIGHT-2, .velocity.x = 0, .velocity.y =0, .len = 15, .vertical = FALSE};
    LEVEL level = {.dificult = 1};
    FRAME frameGame = {.height = MAP_HEIGHT, .width = MAP_WIDTH};
    loadMap(&level.map, map); 
    cpMaptoFrame(&frameGame, level);

    configWindow();
	frameDraw(frameGame);
	while(ch != ESC){ // Enquanto a tecla ESC nao for pressionada
        if(millis % 20 == 0){
            ch = getch();
            padControl(&pad, &frameGame, &level, ch);
        }
        if(millis % 45 == 0)
    	   ballControl(&ball, &pad, &frameGame, &level);
        frameDraw(frameGame);
        refresh(); //atualiza a tela
        usleep(1000); //1 millisegundo
        millis ++;
    }
    endwin();
    return 0;
}
