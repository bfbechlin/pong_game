#include "./headers/header.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void seedGen(){
	srand(time(0));
	// Tornando números randomicos entre 0 e o intervalo máximo para funcionamento do algoritmo
	rmarin_(31328*(rand()/RAND_MAX),30081*(rand()/RAND_MAX));
}

// Simulando um cara ou coroa com uma moeda "viciada" com probabilidade p
BOOL randBinary(float p){
	float random;
	ranmar1_(&random);

	random *= 2*p;
	return (int)random;
}

int randNumber(int n){
	float random;
	ranmar1_(&random);

	// Tornando o número random entre [1, n+1)
	random = n*random + 1;
	return (int)random;
}