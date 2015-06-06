#include "./headers/header.h"

int main(){
    long unsigned int millis;
	int ch = -1;
    int choice; /* Variavel usada para selecionar a escolha do Menu inicial */
    char map[11] = "maps/0.txt";
	millis = 0;
    WINDOW *mainWin, *statsWin;
    BALL ball = {.position.x = 2*MAP_WIDTH/3, .position.y = MAP_HEIGHT-3, .velocity.x = 1, .velocity.y =-1, .enabled = TRUE};
    PADDLE pad = {.position.x = MAP_WIDTH/2, .position.y = MAP_HEIGHT-2, .velocity.x = 0, .velocity.y =0, .len = 15, .vertical = FALSE};
    LEVEL level = {.dificult = 1};
    FRAME frameGame = {.height = MAP_HEIGHT, .width = MAP_WIDTH};
    loadMap(level.map, map); 
    cpMaptoFrame(&frameGame, level);
    
    configWindow();
    
    /* Chama o menu inicial que retorna a opcao escolhida*/
    choice = configMenu(); 
    
    /* Cria as duas janelas de jogo */
    mainWin = create_newwin(MAINW_HEIGHT, MAINW_WIDTH, MAINW_POSY, MAINW_POSX);
    statsWin = create_newwin(STATSW_HEIGHT, STATSW_WIDTH, STATSW_POSY, STATSW_POSX);

    /* Switch das opcoes do menu
       choice=1 -> Partida contra CPU
       choice=2 -> Partida contra P2
       choice=3 -> Mostra janela com o recorde
       choice=4 -> Sai do jogo */
    switch(choice){
        case 1: 
	        //frameDraw(mainWin, frameGame); /* Escreve o jogo na janela principal */ 
            //wrefresh(mainWin);
            //mvwprintw(statsWin, 0, 0, "INFO DO JOGO!"); /* Escreve algumas informacoes na janela de stats */
            //wrefresh(statsWin);
	        while(ch != ESC){ // Enquanto a tecla ESC nao for pressionada
                if(millis % 20 == 0){
                    ch = getch();
                    padControl(&pad, &frameGame, &level, ch);
                }
                if(millis % 45 == 0)
    	            ballControl(&ball, &pad, &frameGame, &level);
                frameDraw(mainWin, frameGame);
                //box(mainWin, 0, 0);
                wrefresh(mainWin); /* atualiza a tela principal */ 
                mvwprintw(statsWin, STATSW_HEIGHT/2, (STATSW_WIDTH-13)/2, "INFO DO JOGO!"); /* Escreve algumas informacoes na janela de stats */
                box(statsWin, 0, 0);
                wrefresh(statsWin);
                usleep(1000); //1 millisegundo
                millis ++;
            }
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            break;
    }
    endwin();
    return 0;
}
