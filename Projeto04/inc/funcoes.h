//Integrantes
//Gabriela Moraes - 16/0006872
//Guilherme Siqueira - 16/0007763
//Kamilla Costa - 16/0010969

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#ifdef WIN32
    #include <windows.h>
    #define LIMPA_TELA system("cls")
    #define LIMPA_BUFFER fflush(stdin)
#else
    #include <stdio_ext.h>
    #include <unistd.h>
    #define LIMPA_TELA system("clear")
    #define LIMPA_BUFFER __fpurge(stdin)
#endif

//Constantes
#define NUMMAXVOOS 64
#define NUMMINVOOS 20
#define NUMMAXAPROXDECOLAGEM 32
#define NUMMINAPROXDECOLAGEM 10
#define NUMMAXACOMBUSTIVEL 12
#define NUMMINACOMBUSTIVEL 0


//Structs


//Prototipos
int sorteiaNumero(int, int, int, int*);


/*
//Codigos de erro

*/
