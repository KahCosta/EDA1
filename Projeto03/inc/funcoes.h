//Integrantes
//Gabriela Moraes - 16/0006872
//Guilherme Siqueira - 16/0007763
//Kamilla Costa - 16/0010969

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

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
#define NOMEARQUIVO "contatos.txt"
#define MAXNOMEENDERECO 101 // contar o terminador
#define MAXTELEFONEDATA 11 //contar o terminador
#define SAIR 0
#define INSERIR 1
#define REMOVER 2
#define VISUALIZARNOME 3
#define VISUALIZARORDEMALFABETICA 4
#define FIMREGISTRO '$'

//Structs
typedef struct Contato{
  char nomeCompleto[MAXNOMEENDERECO];
  char telefone[MAXTELEFONEDATA];
  char endereco[MAXNOMEENDERECO];
  unsigned int cep; //8 numeros
  char dataNascimento[MAXTELEFONEDATA];
}contato;

typedef struct No{
  struct No *anterior;
  contato conteudo;
  struct No *proximo;
}No;

//Prototipos
void darBoasVindas();
FILE* abreArquivo(char *);
int menu();
int calculaQtdRegistros(FILE *);
void leArquivo(FILE *, int);
contato insereDadosContato();
void validaNome(char *);
void validaTelefone(char *);
void validaDataNascimento(char *);
void validaOpcao(char);
No* insereInicioLista(No *, contato);

/*
//Codigos de erro
1-> Falha ao abrir o arquivo
2-> Falha na alocação
*/
