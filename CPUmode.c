#include "./headers/header.h"

void CPUinitGame(){
	long unsigned int millis;
	int ch;
	// LÓGICA
	// Iniciando array de bolas.
	BALL ball[MAXBALL];
	// Iniciando pads. PADS distintos e poucos inicialização inline.
	PADDLE pad[2] = {{.position.x = MAP_WIDTH/2, .position.y = 1, .velocity.x = 0, 
		.velocity.y = 0, .len = 15, .charCode = PAD1H_BLOCK, .botMode = TRUE, .vertical = FALSE},
		{.position.x = MAP_WIDTH/2, .position.y = MAP_HEIGHT-2, .velocity.x = 0, 
		.velocity.y = 0, .len = 15, .charCode = PAD2H_BLOCK, .botMode = FALSE, .vertical = FALSE,
		.advanceKey = KEY_LEFT, .regressKey = KEY_RIGHT}};
	// Iniciando LEVEL
	LEVEL level = {.dificult = 0, .mode = PvsB, .nPad = 2, .nBall =0};
	
	// GRÁFICA
	// Iniciando janelas
	WINDOW *mainWin, *statsWin;
	// Iniciando frame
	FRAME frameGame = {.height = MAP_HEIGHT, .width = MAP_WIDTH};

	// Gerando as seed para os números randomicos
	seedGen(); 
	// Certificando-se que estarão desativadas.
	ballNewLevel(ball);
	// Sorteando e carregando mapa.
	loadLevel(&level);

	cpMaptoFrame(&frameGame, level);
	// Cria as duas janelas de jogo 
    mainWin = create_newwin(MAINW_HEIGHT, MAINW_WIDTH, MAINW_POSY, MAINW_POSX);
    statsWin = create_newwin(STATSW_HEIGHT, STATSW_WIDTH, STATSW_POSY, STATSW_POSX);

	millis = 0;
	padControl(&pad[0], &frameGame, &level, ch);
	while(ch != ESC){ // Enquanto a tecla ESC nao for pressionada
        if(millis % 20 == 0){
            ch = getch();
            padControl(&pad[1], &frameGame, &level, ch);
        }
        if(millis % 45 == 0)
            ballControl(ball, pad, &frameGame, &level);
        if(millis % 3000 == 0){ // Adding ball
        	if(level.nBall < MAXBALL)
        		ballAdd(ball, pad, &level);
        }
        frameDraw(mainWin, frameGame);
        box(mainWin, 0, 0);
        wrefresh(mainWin); // atualiza a tela principal  
        mvwprintw(statsWin, STATSW_HEIGHT/2, (STATSW_WIDTH-13)/2, "INFO DO JOGO!"); // Escreve algumas informacoes na janela de stats 
        box(statsWin, 0, 0);
        wrefresh(statsWin);
   	    usleep(1000); //1 millisegundo
        millis ++;
    }
    endwin();
}
