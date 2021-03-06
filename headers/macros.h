#ifndef MACROS_H
#define MACROS_H

// BOOL
#define TRUE 1
#define FALSE 0

// ** PROTOCOLO PARA AS JANELAS**
/*
	Aqui está descrito as definições de tamanho de cada janela.
	Como também sua posição e algumas outras informações relacionadas.
*/
// WINDOW SIZE
#define SCREEN_WIDTH 122
#define SCREEN_HEIGHT 42

// MAIN WINDOW INFO
#define MAINW_WIDTH 82
#define MAINW_HEIGHT 42
#define MAINW_POSX 0
#define MAINW_POSY 0

// STATS WINDOW SIZE
#define STATSW_WIDTH 40
#define STATSW_HEIGHT 42
#define STATSW_POSX 83
#define STATSW_POSY 0

// MENU INICIAL SIZE
#define MENU_WIDTH 30
#define MENU_HEIGHT 10

// MAP SIZE
#define MAP_WIDTH 82
#define MAP_HEIGHT 42
// ****

// **PROTOCOLO PARA FRAME**
/*
	Aqui estão descritos a codificação para os blocos usados.
	Ou seja, todos o objetos munidos de movimentação ou não,
		estão tem um código para ser identificado e a seguir
		está descrito cada um deles.
*/
// ITEM VAZIO
#define VOID_BLOCK 0

// BOLA
#define BALL_BLOCK 1

// PADS (horizontais e verticais)
/* 	Também é importante saber que o menor indice é o mais perto
		da origem do sitema de coordenadas. Por exemplo, o
		PAD1_H é a plataforma de cima visto que está mais próximo
		de y = 0;
*/
#define PAD1H_BLOCK 2
#define	PAD2H_BLOCK 3
#define PAD1V_BLOCK 4
#define	PAD2V_BLOCK 5

// BARREIRAS
#define BARRIER_BLOCK 6

// PAREDES Inicial 20
#define TOP_BLOCK 20
#define BOT_BLOCK 21
#define LEFT_BLOCK 22
#define RIGHT_BLOCK 23
#define CORNER_BLOCK 24

#define SHIFT_PAD 2

// ****

// **PROTOCOLO PARA A ESTRUTURA LEVEL **
// MODE
#define PvsB 0
#define PvsP 1
// 4 pads
#define PvsB4 2
#define PvsP4 3

// NÚMERO MÁXIMO DE BOLAS
#define MAXBALL 5
// NÚMERO DE MAPAS
#define NMAPS 5

#define BALL_VEL 75
#define BOT_VEL 85
// VELOCIDADES

// ASCII
#define SHIFTNUM 48

// TECLAS
#define ESC 27
#define ENTER 10

// **PROTOCOLO PARA A ESTRUTURA RECORDE **
// NUMERO MAXIMO DE CARACTERES DO NOME DO JOGADOR
#define NAME_LEN 20
#endif
