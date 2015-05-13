/*
	Para instalar a biblioteca curses.h use o seguinte comando:
	# sudo apt-get install libncurses5-dev
	Para compilar deve ser inserido o argumento -lncurses
*/

#include <stdio.h>
#include <ncurses.h>

#define WIDTH 80
#define HEIGHT 25

struct paddle{
	/*Estrutura para as raquetes
	guarda posicao no eixo X, direcao no eixo X e posicao no eixo Y*/
	int posX;
	int dirX;
	int posY;
};

struct ball{
	int posX;
	int posY;
	int dirX;
	int dirY;
};

void setCursor(int x,int y){
    move(y, x);
}

int main()
{
    int i, j;
    struct ball b1 = {.posX=WIDTH/2, .posY=HEIGHT/2, .dirX=1, .dirY=1}; 
    struct paddle p1 = {.posX=WIDTH/2, .posY=HEIGHT-2, .dirX=0};
   
    initscr(); //inicializa ncurses
    curs_set(FALSE); //oculta o cursor do terminal
    noecho(); //nao exibe as teclas pressionadas
    clear();
    //raw(); //getch nao interromper a execucao
    timeout(0); //tempo limite para o usuario pressionar a tecla
    keypad(stdscr, TRUE); //habilita setas direcionais e outras teclas de controle
    int ch = 0;

    // desenha a tela
    for(i=0; i<HEIGHT; i++){
        for(j=0; j<WIDTH; j++){
            if(i == 0 || i == HEIGHT-1) printw("X");
            else if(j == 0 || j == WIDTH-1) printw("X");
            else printw (" ");
        }
        printw("\n");
    }

     while((ch = getch()) != 27){ // Enquanto a tecla ESC nao for pressionada

        setCursor(b1.posX, b1.posY); // altera a posicao do cursor para o da bola
        printw(" "); // imprime um espaco sobre a bola

        // verifica colisoes
        if(b1.posX+b1.dirX == 0 || b1.posX+b1.dirX == WIDTH-1) b1.dirX*=-1;
        if(b1.posY+b1.dirY == 0 || b1.posY+b1.dirY == HEIGHT-1) b1.dirY*=-1;

        //movimenta a bola
        b1.posX += b1.dirX;
        b1.posY += b1.dirY;

        setCursor(b1.posX, b1.posY); //altera a posicao do cursor para nova posica da bola
        printw("O"); //imprime a bola
        
        setCursor(p1.posX, p1.posY); // altera a posicao do cursor para o do paddle
        printw(" "); // imprime um espaco sobre o paddle
        
        // le entrada do usuario para controlar paddle
        switch(ch){
            case KEY_LEFT:
                if(p1.posX>1) p1.dirX=-1;
                else p1.dirX=0;
                p1.posX += p1.dirX;
                break;
            case KEY_RIGHT:
                if(p1.posX<(WIDTH-2)) p1.dirX=1;
                else p1.dirX=0;
                p1.posX += p1.dirX;
                break;
        }
        
        setCursor(p1.posX, p1.posY); //altera a posicao do cursor para nova posica do paddle
        printw("#"); //imprime o paddle
        
        refresh(); //atualiza a tela
        usleep(1000000/30); //30 frames por segundo
    }
    endwin(); //finaliza o ncurses
    return 0;
}
