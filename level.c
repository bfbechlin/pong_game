#include <curses.h>
#include "./headers/types.h"
#include "./headers/macros.h"
#include "./headers/functions.h"

void loadMap(int barrerTable[GAME_HEIGHT][GAME_WIDTH], char* fileName){
    FILE *file;
	char c;
    int i, j;

    file = fopen(fileName, "r");
    for(i = 0; i < GAME_HEIGHT; i ++){
        for(j = 0; j < GAME_WIDTH; j ++){
			c = fgetc(file);
			if(c == 'X')
                barrerTable[i][j] = 5;
            if(c == '_')
                barrerTable[i][j] = 0;
            if(j == 0)
                barrerTable[i][j] = 3;
            if(j == GAME_WIDTH-1)
                barrerTable[i][j] = 4;
            if(i == 0) 
                barrerTable[i][j] = 1;
            if(i == GAME_HEIGHT-1)
                barrerTable[i][j] = 2;
        }
    }
    fclose(file);
    printf("Termino\n");
}