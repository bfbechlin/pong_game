#include "./headers/header.h"

void CPUinitGame(){
	long unsigned int millis;
	clock_t start, end;
	double cpu_time_used;

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
		.velocity.y = 0, .len = 20, .charCode = PAD1H_BLOCK, .botMode = TRUE, .vertical = FALSE
		, .advanceKey = 'a', .regressKey = 'd', .speed = 80},

		{.position.x = (MAP_WIDTH - 20)/2, .position.y = MAP_HEIGHT-2, .velocity.x = 0,
		.velocity.y = 0, .len = 20, .charCode = PAD2H_BLOCK, .botMode = FALSE, .vertical = FALSE,
		.advanceKey = KEY_LEFT, .regressKey = KEY_RIGHT, .speed = 25}
		};
	// Iniciando LEVEL
	LEVEL level = {.dificult = 0, .mapCode = 0, .mode = PvsB, .errorProb = 0.2, .nPad = 2, .nBall =0, .newBallTime = 30,
		.newBallCurrentTime = 3, .p1Score = 1, .p2Score = 1};
	level.mapCode = randNumber(5);
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
	modeGamewrite(statsFrame, &level);
	padControl(&pad[0], ball, gameFrame, &level, ch);
	while(ch != ESC){ // Enquanto a tecla ESC nao for pressionada
		start = clock();
        attGame = FALSE;
        attStats = FALSE;

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

		if(millis % pad[0].speed  == 0){
            padControl(&pad[0], ball, gameFrame, &level, ch);
            attGame = TRUE;
        }
        if(millis % pad[1].speed  == 0){
            ch = getch();
            padControl(&pad[1], ball, gameFrame, &level, ch);
            attGame = TRUE;
        }

        if(level.p1Score < 1){
            //PLAYER GANHOU - JOGO RECOMEÇA COM NIVEL MAIS ALTO
			blinkPlayer(statsWin, statsFrame, statsColorFrame, 1);
			if(level.dificult < 20)
				newLevel(&level, statsFrame, gameFrame, ball, pad);
			else{
				changeRecord(&level);
            	ch = ESC; //Força saida para o menu
			}
            attGame = TRUE;
            attStats = TRUE;
        }

        if(level.p2Score < 1){
            //PLAYER PERDEU - COMPARA NIVEL COM O RECORDE ATUAL E MODIFICA, OU VOLTA PARA O MENU
			blinkPlayer(statsWin, statsFrame, statsColorFrame, 2);
            if(compareRecord(&level))
                changeRecord(&level);
            ch = ESC; //Força saida para o menu
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
		end = clock();
		cpu_time_used = (((double) (end - start)) / CLOCKS_PER_SEC) * 1000; // /mili
   	    usleep(1000 - (int)cpu_time_used); //1 millisegundo - execução média
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
	clock_t start, end;
	double cpu_time_used;

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
		.advanceKey = 'a', .regressKey = 'd', .speed = 25},

		{.position.x = (MAP_WIDTH - 20)/2, .position.y = MAP_HEIGHT-2, .velocity.x = 0,
		.velocity.y = 0, .len = 20, .charCode = PAD2H_BLOCK, .botMode = FALSE, .vertical = FALSE,
		.advanceKey = KEY_LEFT, .regressKey = KEY_RIGHT, .speed = 25}
		};
	// Iniciando LEVEL
	LEVEL level = {.dificult = 0, .mapCode = 0, .mode = PvsP, .nPad = 2, .nBall =0, .newBallTime = 30,
		.newBallCurrentTime = 3, .p1Score = 5, .p2Score = 5};
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
	level.mapCode = randNumber(4);
    loadLevel(&level);
    cpMaptoFrame(gameFrame, &level);
    ballNewLevel(ball);
    modeGamewrite(statsFrame, &level);
	padControl(&pad[0], ball, gameFrame, &level, ch);
	while(ch != ESC){ // Enquanto a tecla ESC nao for pressionada
		start = clock();
        attGame = FALSE;
        attStats = FALSE;

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

		if(millis % pad[0].speed  == 0){
            padControl(&pad[0], ball, gameFrame, &level, ch);
            attGame = TRUE;
        }
        if(millis % pad[1].speed  == 0){
            ch = getch();
            padControl(&pad[1], ball, gameFrame, &level, ch);
            attGame = TRUE;
        }
    
        if(level.p1Score < 1){
            //PLAYER 2 GANHOU
			blinkPlayer(statsWin, statsFrame, statsColorFrame, 1);
            attGame = TRUE;
            attStats = TRUE;
            ch = ESC; //força saida para o menu
        }

        if(level.p2Score < 1){
            //PLAYER 1 GANHOU
			blinkPlayer(statsWin, statsFrame, statsColorFrame, 2);
            attGame = TRUE;
            attStats = TRUE;
            ch = ESC; //força saida para o menu
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
		end = clock();
		cpu_time_used = (((double) (end - start)) / CLOCKS_PER_SEC) * 1000; // /mili
		usleep(1000 - (int)cpu_time_used); //1 millisegundo - execução média
        millis ++;
    }
    delwin(statsWin);
    delwin(mainWin);
	delframe(gameFrame);
	delframe(statsFrame);
	delframe(statsColorFrame);
}

void showRecord(){
    FILE *arq;
    WINDOW *recordWin;
    RECORD bufferRecord = {.playerName = " ", .recordLevel = 0};
    int ch = 0;

    recordWin = create_newwin(10, 50, (LINES-10)/2, (COLS-50)/2);

    while(ch != ESC){
        if(arq = fopen("record", "rb")){
            fread(&bufferRecord, sizeof(RECORD), 1, arq);
            fclose(arq);
        }
        mvwprintw(recordWin, 4, (50-strlen(bufferRecord.playerName)-6)/2, "NOME: %s", bufferRecord.playerName);
        mvwprintw(recordWin, 5, 20, "LEVEL: %d", bufferRecord.recordLevel);
        wrefresh(recordWin);

        ch = wgetch(recordWin);
    }
    delwin(recordWin);
}