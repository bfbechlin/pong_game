#include <curses.h>
#include "./headers/types.h"
#include "./headers/macros.h"
#include "./headers/functions.h"

void sceneDraw(LEVEL level){
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
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_GREEN); //inicia um par de cores
    init_pair(3, COLOR_GREEN, COLOR_RED);
    
    attrset(COLOR_PAIR(1));
    // desenha a tela

    setCursor(zero);
    for(i=0; i<GAME_HEIGHT; i++){
        for(j=0; j<GAME_WIDTH; j++){
            if(level.map[i][j] != 0 && level.map[i][j] != 5){
                attron(COLOR_PAIR(2));
                addch(' ');
                attroff(COLOR_PAIR(2));
            }
            else if(level.map[i][j]  == 5){
                attron(COLOR_PAIR(3));
                addch(' ');
                attroff(COLOR_PAIR(3));
            }
            else{ 
                attron(COLOR_PAIR(1));
                addch(' ');
                attroff(COLOR_PAIR(1));
            }
        }
        printw("\n");
    }   
}
void setCursor(COORD dummy){
    //Movendo o cursor
    move(dummy.y, dummy.x);
}
