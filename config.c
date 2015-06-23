#include "./headers/header.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

/*
    ARG = NADA
    Gera duas seeds usando números aleatórios da biblioteca stdlib para inicializar
		o gerador de números aleatórios ranmar.
*/
void seedGen(){
	srand(time(0));
	// Tornando números randomicos entre 0 e o intervalo máximo para funcionamento do algoritmo
	rmarin_(31327*((double)rand()/RAND_MAX),30080*((double)rand()/RAND_MAX));
}

/*
    ARG = float probalidade de sucesso
    Simula um dispusta binária com certa probalidade de sucesso.
	Ex.: probalidade 0.5 = disputa de Cara e Coroa
*/
BOOL randBinary(float p){
	float random;
	ranmar1_(&random);
	if(random <= p)
		return TRUE;
	return FALSE;
}

/*
    ARG = int números distintos
    Simula um dado com n faces, ou seja, probabilidades iguais para cada face.
	Ex.: número de faces 6 = disputa com dados
*/
int randNumber(int n){
	float random;
	ranmar1_(&random);

	// Tornando o número random entre [1, n+1)
	return (int)(n*random + 1);
}
