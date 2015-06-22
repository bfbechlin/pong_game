#include "./headers/header.h"

void CPUinitGame(){
	long unsigned int millis;
	/*
		ch é iniciado pois caso c.c. chamando o menu e voltando para o jogo há problemas
		com pois o ESC fica salvo na variável. Isso acontece devido a todas as vezes
		que o programa entra nesse função ele aloca exatamente da mesma forma a memória
		então o lixo que estaria na variável é os valores da antiga variável.
	*/
	int gameWinPosX, gameWinPosY;
	int ch = 0;
	BOOL attGame, attStats;
	FRAME *gameFrame, *statsFrame, *statsColorFrame;

	// LÓGICA
	// Iniciando array de bolas.
	BALL ball[MAXBALL];
	// Iniciando pads. PADS distintos e poucos inicialização inline.
	PADDLE pad[2] = {
		{.position.x = (MAP_WIDTH - 20)/2, .position.y = 1, .velocity.x = 0,
		.velocity.y = 0, .len = 20, .charCode = PAD1H_BLOCK, .botMode = TRUE, .vertical = FALSE,
		.advanceKey = 'a', .regressKey = 'd'},

		{.position.x = (MAP_WIDTH - 20)/2, .position.y = MAP_HEIGHT-2, .velocity.x = 0,
		.velocity.y = 0, .len = 20, .charCode = PAD2H_BLOCK, .botMode = FALSE, .vertical = FALSE,
		.advanceKey = KEY_LEFT, .regressKey = KEY_RIGHT}
		};
	// Iniciando LEVEL
	LEVEL level = {.dificult = 0, .mapCode = 0, .mode = PvsB, .nPad = 2, .nBall =0, .newBallTime = 30,
		.newBallCurrentTime = 3, .p1Score = 1, .p2Score = 5, .padP1Speed = 20, .padP2Speed = 150};

	// Gerando as seed para os números randomicos
	seedGen();

	// GRÁFICA
	// Iniciando janelas
	WINDOW *mainWin, *statsWin;
	// Iniciando frame

	gameFrame = create_newframe(MAP_HEIGHT, MAP_WIDTH);
	statsFrame = create_newframe(STATSW_HEIGHT, STATSW_WIDTH);
	statsColorFrame = create_newframe(STATSW_HEIGHT, STATSW_WIDTH);

	frameLoad(statsFrame, "frames/stats.fr");
	frameLoad(statsColorFrame, "frames/stats.frc");

	gameWinPosX = (COLS - SCREEN_WIDTH)/2;
    gameWinPosY = (LINES - SCREEN_HEIGHT)/2;
	// Cria as duas janelas de jogo
    mainWin = create_newwin(MAINW_HEIGHT, MAINW_WIDTH, gameWinPosY, gameWinPosX);
    statsWin = create_newwin(STATSW_HEIGHT, STATSW_WIDTH, gameWinPosY, gameWinPosX + (STATSW_WIDTH+1)*2);

	millis = 0;
	newLevel(&level, statsFrame, gameFrame, ball, pad);
	padControl(&pad[0], gameFrame, &level, ch);
	while(ch != ESC){ // Enquanto a tecla ESC nao for pressionada
        attGame = FALSE;
        attStats = FALSE;
        if(millis % level.padP1Speed  == 0){
            ch = getch();
            padControl(&pad[1], gameFrame, &level, ch);
            attGame = TRUE;
        }
        if(millis % level.padP2Speed == 0){
            controlBotPaddle(&pad[0], ball, gameFrame, &level);
            attGame = TRUE;
        }
        if(millis % BALL_VEL == 0){
            ballControl(ball, pad, gameFrame, &level);
        	attGame = TRUE;
        }
        /* Adicionado BOLAS*/
        if(millis % 1000 == 0){
        	level.newBallCurrentTime --;
        	scoreAtt(statsColorFrame, &level);
        	attStats = TRUE;
		}
        if(level.newBallCurrentTime == 0){
       		level.newBallCurrentTime = level.newBallTime;
       		if(level.nBall < MAXBALL){
       			ballAdd(ball, pad, &level);
       			attGame = TRUE;
       		}
       		attStats = TRUE;
       	}

        if(level.p1Score < 1){
            //PLAYER GANHOU - JOGO RECOMEÇA COM NIVEL MAIS ALTO
			blinkPlayer(statsWin, statsFrame, statsColorFrame, 1);
			newLevel(&level, statsFrame, gameFrame, ball, pad);
            attGame = TRUE;
            attStats = TRUE;
        }


        if(attGame == TRUE){
        	gameFrameDraw(mainWin, gameFrame);
        	box(mainWin, 0, 0);
        	wrefresh(mainWin); // atualiza a tela principal
        }
        if(attStats == TRUE){
        	newBallTimeAtt(statsFrame, statsColorFrame,level.newBallCurrentTime);
        	frameDraw(statsWin, statsFrame, statsColorFrame);
        	wrefresh(statsWin);
        }
   	    usleep(880); //1 millisegundo - execução média
        millis ++;
    }
    delwin(statsWin);
    delwin(mainWin);
	delframe(gameFrame);
	delframe(statsFrame);
	delframe(statsColorFrame);
}

void PVPinitGame(){
	long unsigned int millis;
	/*
		ch é iniciado pois caso c.c. chamando o menu e voltando para o jogo há problemas
		com pois o ESC fica salvo na variável. Isso acontece devido a todas as vezes
		que o programa entra nesse função ele aloca exatamente da mesma forma a memória
		então o lixo que estaria na variável é os valores da antiga variável.
	*/
	int gameWinPosX, gameWinPosY;
	int ch = 0;

	BOOL attGame, attStats;
	FRAME *gameFrame, *statsFrame, *statsColorFrame;

	// LÓGICA
	// Iniciando array de bolas.
	BALL ball[MAXBALL];
	// Iniciando pads. PADS distintos e poucos inicialização inline.
	PADDLE pad[2] = {
		{.position.x = (MAP_WIDTH - 20)/2, .position.y = 1, .velocity.x = 0,
		.velocity.y = 0, .len = 20, .charCode = PAD1H_BLOCK, .botMode = FALSE, .vertical = FALSE,
		.advanceKey = 'a', .regressKey = 'd'},

		{.position.x = (MAP_WIDTH - 20)/2, .position.y = MAP_HEIGHT-2, .velocity.x = 0,
		.velocity.y = 0, .len = 20, .charCode = PAD2H_BLOCK, .botMode = FALSE, .vertical = FALSE,
		.advanceKey = KEY_LEFT, .regressKey = KEY_RIGHT}
		};
	// Iniciando LEVEL
	LEVEL level = {.dificult = 0, .mode = PvsP, .nPad = 2, .nBall =0, .newBallTime = 30,
		.newBallCurrentTime = 5, .p1Score = 5, .p2Score = 5};

	// Gerando as seed para os números randomicos
	seedGen();
	// Certificando-se que estarão desativadas.
	ballNewLevel(ball);
	// Sorteando e carregando mapa.
	loadLevel(&level);

	// GRÁFICA
	// Iniciando janelas
	WINDOW *mainWin, *statsWin;
	// Iniciando frame

	gameFrame = create_newframe(MAP_HEIGHT, MAP_WIDTH);
	statsFrame = create_newframe(STATSW_HEIGHT, STATSW_WIDTH);
	statsColorFrame = create_newframe(STATSW_HEIGHT, STATSW_WIDTH);

	cpMaptoFrame(gameFrame, &level);
	frameLoad(statsFrame, "frames/stats.fr");
	frameLoad(statsColorFrame, "frames/stats.frc");

	gameWinPosX = (COLS - SCREEN_WIDTH)/2;
    gameWinPosY = (LINES - SCREEN_HEIGHT)/2;
	// Cria as duas janelas de jogo
    mainWin = create_newwin(MAINW_HEIGHT, MAINW_WIDTH, gameWinPosY, gameWinPosX);
    statsWin = create_newwin(STATSW_HEIGHT, STATSW_WIDTH, gameWinPosY, gameWinPosX + (STATSW_WIDTH+1)*2);

	millis = 0;
	padControl(&pad[0], gameFrame, &level, ch);
	while(ch != ESC){ // Enquanto a tecla ESC nao for pressionada
        attGame = FALSE;
        attStats = FALSE;
        if(millis % 20 == 0){
            ch = getch();
            padControl(&pad[1], gameFrame, &level, ch);
            padControl(&pad[0], gameFrame, &level, ch);
			attGame = TRUE;
        }
        if(millis % BALL_VEL == 0){
            ballControl(ball, pad, gameFrame, &level);
        	attGame = TRUE;
        }
        /* Adicionado BOLAS*/
        if(millis % 1000 == 0){
        	level.newBallCurrentTime --;
        	scoreAtt(statsColorFrame, &level);
        	attStats = TRUE;
		}
        if(level.newBallCurrentTime < 1){
       		level.newBallCurrentTime = level.newBallTime;
       		if(level.nBall < MAXBALL){
       			ballAdd(ball, pad, &level);
       			attGame = TRUE;
       		}
       		attStats = TRUE;
       	}


        if(attGame == TRUE){
        	gameFrameDraw(mainWin, gameFrame);
        	box(mainWin, 0, 0);
        	wrefresh(mainWin); // atualiza a tela principal
        }
        if(attStats == TRUE){
        	newBallTimeAtt(statsFrame, statsColorFrame,level.newBallCurrentTime);
        	frameDraw(statsWin, statsFrame, statsColorFrame);
        	wrefresh(statsWin);
        }
   	    usleep(880); //1 millisegundo - execução média
        millis ++;
    }
    delwin(statsWin);
    delwin(mainWin);
	delframe(gameFrame);
	delframe(statsFrame);
	delframe(statsColorFrame);
}
