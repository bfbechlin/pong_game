#include "./headers/header.h"

void CPUinitGame(){
	long unsigned int millis, segunds;
	int ch;
	BOOL att;

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
	LEVEL level = {.dificult = 0, .mode = PvsB, .nPad = 2, .nBall =0, .p1Score = 0, .p2Score = 0};
	
	// GRÁFICA
	// Iniciando janelas
	WINDOW *mainWin, *statsWin;
	// Iniciando frame
	FRAME frameGame = {.height = MAP_HEIGHT, .width = MAP_WIDTH};
	FRAME frameStats = {.height = STATSW_HEIGHT, .width = STATSW_WIDTH};
	// Gerando as seed para os números randomicos
	seedGen(); 
	// Certificando-se que estarão desativadas.
	ballNewLevel(ball);
	// Sorteando e carregando mapa.
	loadLevel(&level);


	cpMaptoFrame(&frameGame, level);
	loadStatsFrame(&frameStats, "maps/stats.frame");
	// Cria as duas janelas de jogo 
    mainWin = create_newwin(MAINW_HEIGHT, MAINW_WIDTH, MAINW_POSY, MAINW_POSX);
    statsWin = create_newwin(STATSW_HEIGHT, STATSW_WIDTH, STATSW_POSY, STATSW_POSX);

	millis = 0;
	segunds = 0;
	padControl(&pad[0], &frameGame, &level, ch);
	while(ch != ESC){ // Enquanto a tecla ESC nao for pressionada
        att = FALSE;
        if(millis % 20 == 0){
            ch = getch();
            padControl(&pad[1], &frameGame, &level, ch);
            att = TRUE;
        }
        if(millis % 55 == 0){
            ballControl(ball, pad, &frameGame, &level);
        	att = TRUE;
        }
        if(millis % 3000 == 0){ // Adding ball
        	if(level.nBall < MAXBALL){
        		ballAdd(ball, pad, &level);
        		att = TRUE;
        	}
        }
        if(att == TRUE){
        	frameDraw(mainWin, frameGame);
        	box(mainWin, 0, 0);
        	wrefresh(mainWin); // atualiza a tela principal  

        	statsFrameDraw(statsWin, frameStats);
        	wrefresh(statsWin);
        }
   	    usleep(1000); //1 millisegundo
        millis ++;
        if(millis % 1000 == 0)
        	segunds ++;
    }
    endwin();
}
