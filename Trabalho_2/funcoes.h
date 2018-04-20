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
#define ASPHAULTFILE "asphalt_"
#define GRASSFILE "grass_"
#define EXTENSION ".txt"

int sorteiaNumero();
int validaNumeroSorteado(int, int *);
void selecionaImagens(int *);
void preencheVetor();
void abreArquivo();
void leArquivo();
void fechaArquivo();
void leImagem();
