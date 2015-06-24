#include "./headers/header.h"

/*
    ARG = ponteiro para uma tabela de barreiras, string nome do arquivo
    Realiza o load do mapa substituindo os caracteres para o padrão usado
        nos frames.
    Usado somente para carregar o mapa para estrutura level, devido ao projeto
        usar frames então no level só disponível o mapa do jogo sem outros
        objetos
*/
void loadMap(char barrerTable[MAP_HEIGHT][MAP_WIDTH], char* fileName){
    FILE *file;
	char c;
    int i, j;

    file = fopen(fileName, "r");
    // Escrevendo no centro da matriz deixando caixa de fora
    // Segundo indice percorre uma posição a mais pois o arquivo tem '\n'
    for(i = 1; i < MAP_HEIGHT-1; i ++){
        for(j = 1; j < MAP_WIDTH; j ++){
			c = fgetc(file);
			if(c == 'X')
                barrerTable[i][j] = BARRIER_BLOCK;
            if(c == '_')
                barrerTable[i][j] = VOID_BLOCK;
        }
    }
    // Adiciona as paredes ao redor do mapa
     for(i = 0; i < MAP_HEIGHT; i ++){
        for(j = 0; j < MAP_WIDTH; j ++){
            if(j == 0)
                barrerTable[i][j] = LEFT_BLOCK;
            if(j == MAP_WIDTH-1)
                barrerTable[i][j] = RIGHT_BLOCK;
            if(i == 0)
                barrerTable[i][j] = TOP_BLOCK;
            if(i == MAP_HEIGHT-1)
                barrerTable[i][j] = BOT_BLOCK;
        }
    }
    fclose(file);
}

/*
    ARG = ponteiro para FRAME, ponteiro para LEVEL
    Copia o mapa disponível na estrutura level para a estrutura de frame que
        posteriamente será impresso na tela
*/
void cpMaptoFrame(FRAME *frame, LEVEL *level){
    int i,j;
    for(i = 0; i < frame->height; i ++){
        for(j = 0; j < frame->width; j ++){
            frame->src[i][j] = level->map[i][j];
        }
    }
}

/*
    ARG = ponteiro para LEVEL
    Realiza o conversão do código do mapa do jogo para o caminho em que se
        encontra esse mapa e então já carrega esse mapa para o LEVEL
*/
void loadLevel(LEVEL *level){
    char mapPath[12] = "maps/X.txt";
    mapPath[5] = level->mapCode + '0';
    loadMap(level->map, mapPath);
}

/*
    ARG = ponteiro para LEVEL, ponteiro para FRAME do status do jogo, ponteiro para
    FRAME de jogo, ponteiro para todas as bolas, ponteiro para todos pads
    Realiza todos loads e cálculos necessário para regular dificuldade além de
        atualizar já o frame do status com as novas informações do jogo.
    Cálculos:
        Troca o mapa de jogo
        Aumenta dificuldade
        Dimunui o tempo respawn de novas bolas
        Diminui exponencialmente a probabilidade de erro do BOT
        Aumenta velocidade do BOT
        Diminui o pad do player
*/
void newLevel(LEVEL *level, FRAME *statsFrame, FRAME *gameFrame, BALL *ball, PADDLE *pad){
    FILE *arq;
    RECORD bufferRecord = {.recordLevel = 0, .playerName = " "};

    if(arq = fopen("record", "rb")){
        fread(&bufferRecord, sizeof(RECORD), 1, arq);
        fclose(arq);
    }
    frameAddNumber(statsFrame, bufferRecord.recordLevel, 2, 19, 10); //atualiza statsFrame com recorde atual

    if(level->mapCode >= 5) //seleciona um novo mapa na ordem
        level->mapCode = 1;
    else level->mapCode++;

    level->dificult++;

    frameAddNumber(statsFrame, level->dificult, 2, 21, 12); //atualiza statsFrame com o numero do novo nivel de dificuldade

    if(level->newBallTime > 7) //diminui o tempo para surgir novas bolas
        level->newBallTime = (int)(level->dificult*-1.052 + 29);

    // Inicia em 0.2 e decai exponencialmente até 0.02 na dificuldade 15 aproximadamente
    if(level->errorProb > 0.02)
        level->errorProb = pow(0.985, level->dificult) - 0.78;
    level->nBall = 0;
    level->newBallCurrentTime = 3;
    level->p1Score = 5;
    level->p2Score = 5;

    loadLevel(level); //carrega o mapa do novo nivel
    cpMaptoFrame(gameFrame, level); //copia para o frame do jogo
    ballNewLevel(ball); // Zera as bolas ativas

    // a cada 5 niveis de dificuldade reduz em um a largura do padP1
    if(level->dificult % 5 == 0)
        pad[1].len -= 2;
    if(pad[0].speed > 35) //aumenta taxa de atualizaçao do bot
        pad[0].speed = (int) BOT_VEL*pow(0.96, (level->dificult -1));
}
