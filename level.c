#include "./headers/header.h"

void loadMap(int barrerTable[MAP_HEIGHT][MAP_WIDTH], char* fileName){
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
                barrerTable[i][j] = BLOCK_WALL;
            if(c == '_')
                barrerTable[i][j] = VOID_WALL;
        }
    }
    // Adiciona as paredes ao redor do mapa
     for(i = 0; i < MAP_HEIGHT; i ++){
        for(j = 0; j < MAP_WIDTH; j ++){
            if(j == 0)
                barrerTable[i][j] = LEFT_WALL;
            if(j == MAP_WIDTH-1)
                barrerTable[i][j] = RIGHT_WALL;
            if(i == 0)
                barrerTable[i][j] = TOP_WALL;
            if(i == MAP_HEIGHT-1)
                barrerTable[i][j] = BOT_WALL;
        }
    }
    // Atualizando os cantos
    barrerTable[0][0] = CORNER_WALL;
    barrerTable[0][MAP_WIDTH-1] = CORNER_WALL;
    barrerTable[MAP_HEIGHT-1][0] = CORNER_WALL;
    barrerTable[MAP_HEIGHT-1][MAP_WIDTH-1] = CORNER_WALL;
    fclose(file);
}