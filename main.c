#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "./headers/types.h"
#include "./headers/macros.h"
#include "./headers/functions.h"

int main(){
	int ch;
	BALL b = {.position.x = WIDTH/2, .position.y = HEIGHT-2, .velocity.x = 1, .velocity.y =-1, .enabled = TRUE};

	sceneDraw();
	while((ch = getch()) != ESC) // Enquanto a tecla ESC nao for pressionada
    {
    	ballControl(&b);
        refresh(); //atualiza a tela
        usleep(1000000/30); //30 frames por segundo
    }
    endwin();
    return 0;
}
void sceneDraw(){
    int i, j;
    COORD zero = {.x = 0, .y = 0};
    initscr(); //inicializa ncurses
    curs_set(FALSE); //oculta o cursor do terminal
    noecho(); //nao exibe as teclas pressionadas
    cbreak(); //getch nao interromper a execucao
    timeout(0); //tempo limite para o usuario pressionar a tecla
    clear();
    start_color(); //inicia terminal com cores
    keypad(stdscr, TRUE); //habilita setas direcionais e outras teclas de controle
    init_pair(1, COLOR_RED, COLOR_GREEN); //inicia um par de cores
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    
    attrset(COLOR_PAIR(1));
    // desenha a tela

    setCursor(zero);
    for(i=0; i<HEIGHT; i++){
        for(j=0; j<WIDTH; j++){
            if(i == 0 || i == HEIGHT-1){
                attron(COLOR_PAIR(1));
                addch('+');
                attroff(COLOR_PAIR(1));
            }
            else if(j == 0 || j == WIDTH-1){
                attron(COLOR_PAIR(1));
                addch('+');
                attroff(COLOR_PAIR(1));
            }
            else{ 
                attron(COLOR_PAIR(2));
                addch(' ');
                attroff(COLOR_PAIR(2));
            }
        }
        printw("\n");
    }   
}
void setCursor(COORD dummy){
    //Movendo o cursor
    move(dummy.y, dummy.x);
}
