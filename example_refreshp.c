/*
	Para instalar a biblioteca curses.h use o seguinte comando:
	# sudo apt-get install libncurses5-dev
	Para compilar deve ser inserido o argumento -lncurses
*/

#include <stdio.h>
#include <curses.h>

#define WIDTH 30
#define HEIGHT 14
#define TRUE 1
#define FALSE 0

typedef char boolean;

typedef struct{
	unsigned int posX;
	unsigned int posY;
	int velX;
	int velY;
	boolean enabled;
	
}ball;

void setCursor(int x,int y){
    move(y, x);
}

void collisionVerificationScene(ball *dummy_ball){
	if(dummy_ball->posX + dummy_ball->velX == 0 || dummy_ball->posX + dummy_ball->velX == WIDTH-1) 
		dummy_ball->velX*=-1;
    if(dummy_ball->posY + dummy_ball->velY == 0 || dummy_ball->posY + dummy_ball->velY == HEIGHT-1) 
		dummy_ball->velY*=-1;
}

void attBallPos(ball *dummy_ball){
	dummy_ball->posX += dummy_ball->velX;
    dummy_ball->posY += dummy_ball->velY;
}
int main(int argc, char *argv[])
{
    int i, j;
	ball b = {.posX=WIDTH/2, .posY=HEIGHT/2, .velX=1, .velY=1, .enabled = TRUE};
	

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

        setCursor(b.posX, b.posY); // altera a posicao do cursor para o da bola
        printw(" "); // imprime um espaco sobre a bola

        // verifica colisoes
        collisionVerificationScene(&b);

        //movimenta a bola
        attBallPos(&b);

        setCursor(b.posX, b.posY); //altera a posicao do cursor paraa nova posica da bola
        printw("O"); //imprime a bola

        refresh(); //atualiza a tela
        usleep(1000000/30); //30 frames por segundo
    }
    endwin(); //finaliza o ncurses
    return 0;
}

