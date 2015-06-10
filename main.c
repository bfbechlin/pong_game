#include "./headers/header.h"

int main(){
    int choice; /* Variavel usada para selecionar a escolha do Menu inicial */
    
    // Configurações gerais da ncurses, bem como cores do terminal
    configWindow();
    
    /* Chama o menu inicial que retorna a opcao escolhida*/
    

    /* Switch das opcoes do menu
       choice=1 -> Partida contra CPU
       choice=2 -> Partida contra P2
       choice=3 -> Mostra janela com o recorde
       choice=4 -> Sai do jogo */
    do{
        switch(choice = configMenu()){
            case 1: 
    	        CPUinitGame();
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
    }while(choice != 4);
    endwin();
    return 0;
}
