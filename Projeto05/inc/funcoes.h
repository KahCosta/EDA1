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
#include <string.h>


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


//Structs
typedef struct Arvore{
  int info;
  struct Arvore *direita;
  struct Arvore *esquerda;
}Arvore;

//Prototipos
int menu();
int validateNumbers(int, int, int);
int calculateQuantityOfNumbers(FILE *);
FILE* openArchive(char *);
void readNumbersFromArchive(FILE *, int, int *);
Arvore* createNewNode(int);
Arvore* insert(Arvore *, Arvore *);
Arvore* loadTreeFromFile(char *);
void showTree();
void isFull();
void searchValue();
void getHeight();
void removeValue();
void printInOrder();
void printPreOrder();
void printPostOrder();
void balanceTree();
