#include "./headers/header.h"

int main(){
    int choice, PosX, PosY; /* Variavel usada para selecionar a escolha do Menu inicial */
    WINDOW *menuWin, *homeWin;
    FRAME *homeFrame;
    // Configurações gerais da ncurses, bem como cores do terminal
    configWindow();

    // Gerando as seed para os números randomicos
	seedGen();

    /* Criando janelas */
    PosX = (COLS - MENU_WIDTH)/2;
    PosY = (LINES - MENU_HEIGHT)/2;
    menuWin = create_newwin(MENU_HEIGHT, MENU_WIDTH, PosY, PosX);

    PosX = (COLS - SCREEN_WIDTH)/2;
    PosY = (LINES - SCREEN_HEIGHT)/2;
    homeWin = create_newwin(SCREEN_HEIGHT, SCREEN_WIDTH, PosY, PosX);

    homeFrame = create_newframe(SCREEN_HEIGHT, SCREEN_WIDTH);
    frameLoad(homeFrame, "frames/home.fr");

    /* Chama o menu inicial que retorna a opcao escolhida
        **Switch das opcoes do menu**
       choice=1 -> Partida contra CPU
       choice=2 -> Partida contra P2
       choice=3 -> Mostra janela com o recorde
       choice=4 -> Sai do jogo */
    do{
        homeDraw(homeWin, homeFrame);
        wrefresh(homeWin);
        switch(choice = configMenu(menuWin)){
            case 1:
    	        CPUinitGame();
                break;
            case 2:
                PVPinitGame();
                break;
            case 3:
                showRecord();
                break;
            case 4:
                break;
            default:
                break;
        }
    }while(choice != 4);
    endwin();
    return 0;
}
