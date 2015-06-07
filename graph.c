#include "./headers/header.h"

void frameDraw(FRAME frame){
    int i, j;

    setCursor(0,0);
    for(i=0; i< MAP_HEIGHT; i++){
        for(j=0; j< MAP_WIDTH; j++){
            // PAREDES EXTENAS
            if(frame.src[i][j] >= TOP_BLOCK && frame.src[i][j] <= CORNER_BLOCK)
                addChColor(' ', 2);
            else if(frame.src[i][j]  == BARRIER_BLOCK)
                addChColor(' ', 3);
            else if(frame.src[i][j]  == BALL_BLOCK)
                addChColor('o', 1);
            else if(frame.src[i][j]  == PAD1H_BLOCK)
                addChColor(ACS_DIAMOND, 4);
            else
                addChColor(' ', 1);
        }
        addch('\n');
    }   
}
void setCursor(int y, int x){
    //Movendo o cursor
    move(y, x);
}
void configWindow(){
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
    init_pair(4, COLOR_BLACK, COLOR_BLUE);

    attrset(COLOR_PAIR(1));
}
void addChColor(int ch, int colorPair){
    attron(COLOR_PAIR(colorPair));
    addch(ch);
    attroff(COLOR_PAIR(colorPair));
}