#include "./headers/header.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void seedGen(){
	srand(time(0));
	// Tornando números randomicos entre 0 e o intervalo máximo para funcionamento do algoritmo
	rmarin_(31327*((double)rand()/RAND_MAX),30080*((double)rand()/RAND_MAX));
}

// Simulando um cara ou coroa com uma moeda "viciada" com probabilidade p
BOOL randBinary(float p){
	float random;
	ranmar1_(&random);
	if(random <= p)
		return TRUE;
	return FALSE;
}

int randNumber(int n){
	float random;
	ranmar1_(&random);

	// Tornando o número random entre [1, n+1)
	return n*random + 1;
}
