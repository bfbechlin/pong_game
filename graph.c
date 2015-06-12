#include "./headers/header.h"

int configMenu(){
    WINDOW *menuWin;
    int selected=1;
    int choice=0;
    int c;
    int menuPosX, menuPosY;

    char *opt[] = {
        "vs CPU",
        "vs P2",
        "Recorde",
        "Sair"
    };
    int numOpt = sizeof(opt) / sizeof(char *);

    menuPosX = (COLS - MENU_WIDTH)/2;
    menuPosY = (LINES - MENU_HEIGHT)/2;

    menuWin = newwin(MENU_HEIGHT, MENU_WIDTH, menuPosY, menuPosX);
    keypad(menuWin, TRUE);
    printMenu(menuWin, selected, opt, numOpt);
    while(choice==0){
        switch(c = wgetch(menuWin)){
            case KEY_UP:
                if(selected==1)
                    selected = numOpt;
                else selected--;
                break;
            case KEY_DOWN:
                if(selected==numOpt)
                    selected = 1;
                else selected++;
                break;
            case ENTER:
                choice = selected;
                break;
            default:
                break;
        }
        printMenu(menuWin, selected, opt, numOpt);
    }
    return choice;
}

void printMenu(WINDOW *menuWin, int selected, char *opt[], int numOpt){
    int textPosX=2, textPosY=2, i;
    
    box(menuWin, 0, 0);
    for(i=0;i<numOpt;i++){
        if(selected==i+1){ //Destaca a opcao escolhida
            wattron(menuWin, A_REVERSE);
            mvwprintw(menuWin, textPosY, textPosX, "%s", opt[i]);
            wattroff(menuWin, A_REVERSE);
        }
        else mvwprintw(menuWin, textPosY, textPosX, "%s", opt[i]);
        textPosY++;
    }
    wrefresh(menuWin);
}

WINDOW *create_newwin(int height, int width, int starty, int startx){
    WINDOW *localWin;
    
    localWin = newwin(height, width, starty, startx);
    box(localWin, 0, 0);
    wrefresh(localWin);

    return localWin;
}
void frameDraw(WINDOW *localWin, FRAME frame){
    int i, j;
    
    /* A funcao setCursor parece ser meio redundante ja que a funcao move faz exatamente a mesma coisa 
       Se for por clareza do codigo, daria para modificar a setCursor para setWinCursor e passar junto das cordenadas
       uma WINDOW */
    //setCursor(0, 0);
    wmove(localWin, 0, 0);
    for(i=0; i< MAP_HEIGHT; i++){
        for(j=0; j< MAP_WIDTH; j++){
            // PAREDES EXTENAS
            if(frame.src[i][j] >= TOP_BLOCK && frame.src[i][j] <= CORNER_BLOCK)
                waddchColor(localWin, ' ', 2);
            else if(frame.src[i][j]  == BARRIER_BLOCK)
                waddchColor(localWin, ' ', 3);
            else if(frame.src[i][j]  == BALL_BLOCK)
                waddchColor(localWin, 'o', 1);
            else if(frame.src[i][j]  == PAD1H_BLOCK)
                waddchColor(localWin, ACS_DIAMOND, 2);
            else if(frame.src[i][j]  == PAD2H_BLOCK)
                waddchColor(localWin, ACS_DIAMOND, 4);
            else if(frame.src[i][j]  == PAD1V_BLOCK)
                waddchColor(localWin, ACS_DIAMOND, 2);
            else if(frame.src[i][j]  == PAD2V_BLOCK)
                waddchColor(localWin, ACS_DIAMOND, 4);
            
            else
                waddchColor(localWin, ' ', 1);
        }
        /* Ainda nao descobri o motivo, mas quando trabalhando com WINDOWS nao precisa inserir uma nova linha, ele parece fazer automatico */
        //waddch(localWin, '\n');
    }   
}
void statsFrameDraw(WINDOW *localWin, FRAME frame){
    int i, j;
    
    wmove(localWin, 0, 0);
    for(i = 0; i < frame.height; i++){
        for(j = 0; j< frame.width; j++){
            if(frame.src[i][j] == '_')
                waddchColor(localWin, ' ', 1);
            else if(frame.src[i][j] == '(')
                waddchColor(localWin, ACS_ULCORNER, 1);
            else if(frame.src[i][j] == '{')
                waddchColor(localWin, ACS_LLCORNER, 1);
            else if(frame.src[i][j] == ')')
                waddchColor(localWin, ACS_URCORNER, 1);
            else if(frame.src[i][j] == '}')
                waddchColor(localWin, ACS_LRCORNER, 1);
            else if(frame.src[i][j] == '-')
                waddchColor(localWin, ACS_HLINE, 1);
            else if(frame.src[i][j] == '|')
                waddchColor(localWin, ACS_VLINE, 1);
            else if(frame.src[i][j] == '^')
                waddchColor(localWin, ' ', 3);
            else
                waddchColor(localWin, frame.src[i][j], 1);
        }
    }
}
void loadStatsFrame(FRAME *frame, char *fileName){
    FILE *file;
    char c;
    int i, j;
    // width + 1 pois deve se ler o caracter \n em todas as linhas
    file = fopen(fileName, "r");
    for(i = 0; i < frame->height; i ++){
        for(j = 0; j < frame->width + 1; j ++){
            c = fgetc(file);
            if(c != '\n')
                frame->src[i][j] = c;
        }
    }
    fclose(file);
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
    init_pair(2, COLOR_BLACK, COLOR_GREEN); 
    init_pair(3, COLOR_GREEN, COLOR_RED);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);

    attrset(COLOR_PAIR(1));
}
void waddchColor(WINDOW *localWin,int ch, int colorPair){
    wattron(localWin, COLOR_PAIR(colorPair));
    waddch(localWin, ch);
    wattroff(localWin, COLOR_PAIR(colorPair));
}
