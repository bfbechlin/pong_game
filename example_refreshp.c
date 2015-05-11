/*
	Para instalar a biblioteca curses.h use o seguinte comando:
	# sudo apt-get install libncurses5-dev
	Para compilar deve ser inserido o argumento -lncurses
*/

#include <stdio.h>
#include <curses.h>

#define WIDTH 30
#define HEIGHT 14

void setCursor(int x,int y){
    move(y, x);
}

int main(int argc, char *argv[])
{
    int i, j, posX=WIDTH/2, posY=HEIGHT/2, dirX=1, dirY=1;

    initscr(); //inicializa ncurses
    curs_set(FALSE); //oculta o cursor do terminal
    noecho(); //nao exibe as teclas pressionadas
    cbreak(); //getch nao interromper a execucao
    timeout(0); //tempo limite para o usuario pressionar a tecla
	start_color(); //inicia terminal com cores
	init_pair(1, COLOR_RED, COLOR_GREEN); //inicia um par de cores
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
    int ch = 0;
	
	attron(COLOR_PAIR(1));
    // desenha a tela
    for(i=0; i<HEIGHT; i++){
        for(j=0; j<WIDTH; j++){
            if(i == 0 || i == HEIGHT-1){
				attron(COLOR_PAIR(1));
				printw ("+");
				attron(COLOR_PAIR(1));
			}
            else if(j == 0 || j == WIDTH-1){
				attron(COLOR_PAIR(1));
				printw ("+");
				attron(COLOR_PAIR(1));
			}
            else{ 
				attron(COLOR_PAIR(2));
				printw (" ");
				attron(COLOR_PAIR(2));
			}
        }
        printw("\n");
    }
	attroff(COLOR_PAIR(1));

     while(ch != 27) // Enquanto a tecla ESC nao for pressionada
    {

        setCursor(posX, posY); // altera a posicao do cursor para o da bola
        printw(" "); // imprime um espaco sobre a bola

        // verifica colisoes
        if(posX+dirX == 0 || posX+dirX == WIDTH-1) dirX*=-1;
        if(posY+dirY == 0 || posY+dirY == HEIGHT-1) dirY*=-1;

        //movimenta a bola
        posX += dirX;
        posY += dirY;

        setCursor(posX, posY); //altera a posicao do cursor paraa nova posica da bola
        printw("O"); //imprime a bola

        refresh(); //atualiza a tela
        usleep(1000000/30); //30 frames por segundo
    }
    endwin(); //finaliza o ncurses
    return 0;
}
