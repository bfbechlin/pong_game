#include "./headers/header.h"

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

void cpMaptoFrame(FRAME *frame, LEVEL level){
    int i,j;
    for(i = 0; i < frame->height; i ++){
        for(j = 0; j < frame->width; j ++){
            frame->src[i][j] = level.map[i][j];
        }
    }
}

void loadLevel(LEVEL *level){
    char mapPath[][12] = {"maps/0.txt", "maps/1.txt", "maps/2.txt", "maps/3.txt", "maps/4.txt"}; 
    //level->mapCode = randNumber(NMAPS);
    switch(level->mapCode){
        case 0:
            loadMap(level->map, mapPath[4]);
            break;
        case 1:
            loadMap(level->map, mapPath[1]);
            break;
        case 2:
            loadMap(level->map, mapPath[2]);
            break;
        case 3:
            loadMap(level->map, mapPath[0]);
            break;
        default:
            loadMap(level->map, mapPath[3]);
            break;
        }
}

void increaseLevel(LEVEL *level, PADDLE *pad){            
    if(level->mapCode == 4) //seleciona um novo mapa na ordem
        level->mapCode = 0;
        else level->mapCode++;

    if(level->dificult < 20) //aumenta o marcador do nivel de dificuldade
        level->dificult++;

    if(level->newBallTime > 10) //diminui o tempo para surgir novas bolas
        level->newBallTime--;
              
    if(level->padP2Speed > 50) //aumenta taxa de atualizaçao do bot
        level->padP2Speed-2;
           
    level->nBall =0; //configura os demais parametros
    level->newBallCurrentTime = 3; 
    level->p1Score = 5; 
    level->p2Score = 5; 
            
    loadLevel(level); //carrega o novo nivel
    //millis =0;
            
    // a cada 5 niveis de dificuldade reduz em um a largura do padP1
    if(level->dificult % 5 == 0)
        pad[1].len--;
}
