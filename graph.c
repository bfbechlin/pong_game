#include "./headers/header.h"

int configMenu(WINDOW *menuWin){
    int selected=1;
    int choice=0;
    int c;
    int menuPosX, menuPosY;

    char *opt[] = {
        "Player vs CPU",
        "Two Players",
        "Recorde",
        "Sair"
    };
    int numOpt = sizeof(opt) / sizeof(char *);

    menuPosX = (COLS - MENU_WIDTH)/2;
    menuPosY = (LINES - MENU_HEIGHT)/2;

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

/*
    Algum problema!!!
*/
FRAME *create_newframe(int wid, int hei){
    FRAME *localFrame;

    localFrame->width = wid;
    localFrame->height = hei;
    
    return localFrame;
}

void gameFrameDraw(WINDOW *localWin, FRAME *frame){
    int i, j;
    
    /* A funcao setCursor parece ser meio redundante ja que a funcao move faz exatamente a mesma coisa 
       Se for por clareza do codigo, daria para modificar a setCursor para setWinCursor e passar junto das cordenadas
       uma WINDOW */
    wmove(localWin, 0, 0);
    for(i=0; i< MAP_HEIGHT; i++){
        for(j=0; j< MAP_WIDTH; j++){
            // PAREDES EXTENAS
            if(frame->src[i][j] >= TOP_BLOCK && frame->src[i][j] <= CORNER_BLOCK)
                waddchColor(localWin, ' ', 2);
            else if(frame->src[i][j]  == BARRIER_BLOCK)
                waddchColor(localWin, ' ', 4);
            else if(frame->src[i][j]  == BALL_BLOCK)
                waddchColor(localWin, 'o', 1);
            else if(frame->src[i][j]  == PAD1H_BLOCK)
                waddchColor(localWin, ACS_DIAMOND, 2);
            else if(frame->src[i][j]  == PAD2H_BLOCK)
                waddchColor(localWin, ACS_DIAMOND, 3);
            else if(frame->src[i][j]  == PAD1V_BLOCK)
                waddchColor(localWin, ACS_DIAMOND, 2);
            else if(frame->src[i][j]  == PAD2V_BLOCK)
                waddchColor(localWin, ACS_DIAMOND, 3);
            
            else
                waddchColor(localWin, ' ', 1);
        }
        /* Ainda nao descobri o motivo, mas quando trabalhando com WINDOWS nao precisa inserir uma nova linha, ele parece fazer automatico */
        //waddch(localWin, '\n');
    }   
}
/*
    ARG = ponteiro para window, ponteiro para frame, ponteiro para frame
        Escreve o frame na tela com com a cor definido pelo Frame color.
*/

void statsFrameDraw(WINDOW *localWin, FRAME *frame, FRAME *frameColor){
    int i, j;
    
    wmove(localWin, 0, 0);
    for(i = 0; i < frame->height; i++){
        for(j = 0; j< frame->width; j++){
            if(frame->src[i][j] == '_')
                waddchColor(localWin, ' ', 1);
            else if(frame->src[i][j] == '(')
                waddchColor(localWin, ACS_ULCORNER, 1);
            else if(frame->src[i][j] == '{')
                waddchColor(localWin, ACS_LLCORNER, 1);
            else if(frame->src[i][j] == ')')
                waddchColor(localWin, ACS_URCORNER, 1);
            else if(frame->src[i][j] == '}')
                waddchColor(localWin, ACS_LRCORNER, 1);
            else if(frame->src[i][j] == '-')
                waddchColor(localWin, ACS_HLINE, 1);
            else if(frame->src[i][j] == '|')
                waddchColor(localWin, ACS_VLINE, 1);
            else if(frame->src[i][j] == '^')
                waddchColor(localWin, ' ', 2);
            else if(frame->src[i][j] == '&')
                waddchColor(localWin, ' ', frameColor->src[i][j] - '0');
            else if(frame->src[i][j] == '#')
                waddchColor(localWin, ACS_HLINE, frameColor->src[i][j] - '0');
            else
                waddchColor(localWin, frame->src[i][j], frameColor->src[i][j] - '0');
        }
    }
}
void testeBallTime(FRAME *frame, int newBallTime){
    if(newBallTime > 0)
        frameAddNumber(frame, newBallTime, 2, 22, 33);
}
void frameLoad(FRAME *frame, char *fileName){
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

/*
    ARG = SEM
    Inicializa ncurses e configura todos padrãos que serão usados em todo o resto da
        execução tais como cores, não imprimir os caracters na tela getch não inter-
        romper execução ...
*/
void configWindow(){
    initscr(); //inicializa ncurses
    curs_set(FALSE); //oculta o cursor do terminal
    noecho(); //nao exibe as teclas pressionadas
    cbreak(); //getch nao interromper a execucao
    timeout(0); //tempo limite para o usuario pressionar a tecla
    clear();
    start_color(); //inicia terminal com cores
    keypad(stdscr, TRUE); //habilita setas direcionais e outras teclas de controle

    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Cor padrão
    init_pair(2, COLOR_WHITE, COLOR_GREEN); // Cor pad 1
    init_pair(3, COLOR_WHITE, COLOR_BLUE); // Cor pad 2
    init_pair(4, COLOR_GREEN, COLOR_RED); // Cor BARRER
    init_pair(5, COLOR_RED, COLOR_GREEN); // Cor Oposto BARRER
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_GREEN, COLOR_BLACK);
    init_pair(8, COLOR_BLUE, COLOR_BLACK);
    init_pair(9, COLOR_YELLOW, COLOR_BLACK);
    init_pair(10, COLOR_CYAN, COLOR_BLACK);
    init_pair(11, COLOR_BLACK, COLOR_CYAN);

    attrset(COLOR_PAIR(1));
}

/*
    ARG = pointeiro para window, int caracter, int par de cor
    Escreve determinado caracter na janela com a cor determinada
        pelo argumento.
*/
void waddchColor(WINDOW *localWin, int ch, int colorPair){
    wattron(localWin, COLOR_PAIR(colorPair));
    waddch(localWin, ch);
    wattroff(localWin, COLOR_PAIR(colorPair));
}

/*
    ARG = pointeiro para frame, int número que será colocado, int linha do frame,
        int coluna do frame, int quadrados
    Escreve um número no frame, ainda especificando em quandos elementos da matriz
        o número será colocado. Ex.: 12, usando 3 squares -> 0 1 2.
*/
void frameAddNumber(FRAME *frame, int number, int squares, int line, int colum){
    int i, exp10;
    exp10 = 10;
    frame->src[line][colum + --squares] = number%10 + SHIFTNUM;
    for(i = squares -1; i >= 0 ; i--){
        frame->src[line][colum+i] = number/exp10 + SHIFTNUM;
        exp10 *= 10;
    }
}

/*
    ARG = pointeiro para frame, ponteiro de char que é a palavra, int linha do 
        frame, int coluna do frame
    Escreve uma palavra no frame, quebrando a linha se necessário
*/
void frameAddString(FRAME *frame, char *String, int line, int colum){
    int i, j, lineLen, StringLen;
    j = line;
    lineLen = frame->width;
    StringLen = strlen(String);
    for(i = 0; i < StringLen; i++){
        if(colum+i == lineLen)
            j++;
        frame->src[j][(colum+i)%lineLen] = String[i];
    }
}

/*
    ARG = pointeiro para frame, int número do par de cores, int quadrados, int linha do 
        frame, int coluna do frame
    Troca a cor do quadrado corrente do quadrado.
*/
void frameAddColor(FRAME *frame, int colorPair, int squares, int line, int colum){
    int i, j, lineLen;
    j = line;
    lineLen = frame->width;
    for(i = 0; i < squares; i++){
        if(colum+i == lineLen)
            j++;
        frame->src[j][(colum+i)%lineLen] = colorPair;
    }
}