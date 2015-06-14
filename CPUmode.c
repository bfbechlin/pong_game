#include "./headers/header.h"

void CPUinitGame(){
	long unsigned int millis;
	int segunds, newBallTime;
	/*
		ch é iniciado pois caso c.c. chamando o menu e voltando para o jogo há problemas 
		com pois o ESC fica salvo na variável. Isso acontece devido a todas as vezes
		que o programa entra nesse função ele aloca exatamente da mesma forma a memória
		então o lixo que estaria na variável é os valores da antiga variável.
	*/
	int ch = 0;
	int gameWinPosX, gameWinPosY; 
	BOOL att;
	//FRAME *frameGame, *frameStats, *frameStatsColor;

	// LÓGICA
	// Iniciando array de bolas.
	BALL ball[MAXBALL];
	// Iniciando pads. PADS distintos e poucos inicialização inline.
	PADDLE pad[2] = {
		{.position.x = (MAP_WIDTH - 20)/2, .position.y = 1, .velocity.x = 0, 
		.velocity.y = 0, .len = 20, .charCode = PAD1H_BLOCK, .botMode = TRUE, .vertical = FALSE},
		
		{.position.x = (MAP_WIDTH - 20)/2, .position.y = MAP_HEIGHT-2, .velocity.x = 0, 
		.velocity.y = 0, .len = 20, .charCode = PAD2H_BLOCK, .botMode = FALSE, .vertical = FALSE,
		.advanceKey = KEY_LEFT, .regressKey = KEY_RIGHT}
		};
	// Iniciando LEVEL
	LEVEL level = {.dificult = 0, .mode = PvsB, .nPad = 2, .nBall =0, .p1Score = 0, .p2Score = 0};
	
	// GRÁFICA
	// Iniciando janelas
	WINDOW *mainWin, *statsWin;
	// Iniciando frame
	/*
	frameGame = create_newframe(MAP_HEIGHT, MAP_WIDTH);
	frameStats = create_newframe(STATSW_HEIGHT, STATSW_WIDTH);
	frameStatsColor = create_newframe(STATSW_HEIGHT, STATSW_WIDTH);
	*/
	FRAME frameGame = {.height = MAP_HEIGHT, .width = MAP_WIDTH};
	FRAME frameStats = {.height = STATSW_HEIGHT, .width = STATSW_WIDTH};
	FRAME frameStatsColor = {.height = STATSW_HEIGHT, .width = STATSW_WIDTH};
	// Gerando as seed para os números randomicos
	seedGen(); 
	// Certificando-se que estarão desativadas.
	ballNewLevel(ball);
	// Sorteando e carregando mapa.
	loadLevel(&level);


	cpMaptoFrame(&frameGame, level);
	frameLoad(&frameStats, "maps/frames/stats.fr");
	frameLoad(&frameStatsColor, "maps/frames/stats.frc");
	gameWinPosX = (COLS - SCREEN_WIDTH)/2;
    gameWinPosY = (LINES - SCREEN_HEIGHT)/2;
	// Cria as duas janelas de jogo 
    mainWin = create_newwin(MAINW_HEIGHT, MAINW_WIDTH, gameWinPosY, gameWinPosX);
    statsWin = create_newwin(STATSW_HEIGHT, STATSW_WIDTH, gameWinPosY, gameWinPosX + (STATSW_WIDTH+1)*2);

	millis = 0;
	segunds = 0;
	newBallTime = 10;
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
        if(millis % 10000 == 0){ // Adding ball
        	if(level.nBall < MAXBALL){
        		ballAdd(ball, pad, &level);
        		att = TRUE;
        	}
        }
        if(att == TRUE){
        	gameFrameDraw(mainWin, &frameGame);
        	box(mainWin, 0, 0);
        	wrefresh(mainWin); // atualiza a tela principal  

        	testeBallTime(&frameStats, newBallTime);
        	statsFrameDraw(statsWin, &frameStats, &frameStatsColor);
        	wrefresh(statsWin);
        	
        	
        }
   	    usleep(900); //1 millisegundo
        millis ++;
        if(millis % 1000 == 0){
        	segunds ++;
        	newBallTime --;
        	if(newBallTime == 0)
        		newBallTime = 10;
        }
    }
    delwin(statsWin);
    delwin(mainWin);
}
