#ifndef TYPES_H
#define TYPES_H

// **MACROS**

// SIZE WINDOW
#define WIDTH 80
#define HEIGHT 40

// TECLAS
#define ESC 27
#define LEFT_ARROW  37
#define UP_ARROW 38
#define RIGTH_ARROW 39
#define DOWN_ARROW 40

// BOOL
#define TRUE 1
#define FALSE 0

// **TIPOS**

typedef unsigned char BOOL;

// **ESTRUTURAS**

typedef struct
{
    int x;
    int y;
}COORD;

typedef struct{
    // Posições relacionadas com a primeira posição de um array
    COORD position;
    COORD velocity;
    BOOL enabled;
}BALL;

typedef struct{
    // Posições relacionadas com a primeira posição de um array
    COORD position;
    // Velocidades X e Y
    COORD velocity;
    // Tamanho da plataforma
    unsigned int len;

}PADDLE;

typedef struct{
    // Posições relacionadas com a primeira posição de um array
    char map[HEIGHT][WIDTH];
    // Velocidades X e Y
    int dificult;
    // Tamanho da plataforma
    unsigned int len;
}LEVEL;

#endif