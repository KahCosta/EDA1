#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#ifdef WIN32
    #define LIMPA_TELA system("cls")
#else
    #define LIMPA_TELA system("clear")
#endif

#define TAMIMAGEM 512
#define FILEMAX 50
#define NUMMAX 25
#define REPETIDO 1
#define NREPETIDO 0
#define ASPHAULTFILE "asphalt_"
#define GRASSFILE "grass_"
#define EXTENSION ".txt"

int sorteiaNumero(int *);
//void ordenaVetor(int *);
int comparaVetor(int *, int *);
void abreArquivo(FILE *, int);
void leArquivo(FILE *);
void fechaArquivo(FILE *);
void leImagem();
