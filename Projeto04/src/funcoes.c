//Integrantes
//Gabriela Moraes - 16/0006872
//Guilherme Siqueira - 16/0007763
//Kamilla Costa - 16/0010969

#include "funcoes.h"

int sorteiaNumero(int *combA, int *vetInformacoes){
  int numSorteadoCombA;
  int nVoos, nAproximacoes, nDecolagens;
  nVoos = NUMMINVOOS;
  nAproximacoes = NUMMINAPROXDECOLAGEM;
  nDecolagens = NUMMINAPROXDECOLAGEM;
  numSorteadoCombA = NUMMINACOMBUSTIVEL;
  srand((unsigned) time(NULL));
  //nVoos = ((rand() % 64) + 1);
  nAproximacoes = ((rand() % NUMMAXAPROXDECOLAGEM) + 1);
  nDecolagens = ((rand() % NUMMAXAPROXDECOLAGEM) + 1);
  nVoos = nAproximacoes + nDecolagens;

  printf("\nnVoos: ");
  printf("%d\n", nVoos);
  printf("\nnAproximacoes: %d\n", nAproximacoes);
  printf("\nnDecolagens: %d\n", nDecolagens);
  printf("\n\nVetor de pousos e combustiveis: \n");
  for(int i = 0; i < nAproximacoes; i++){
    numSorteadoCombA = ((rand() % NUMMAXACOMBUSTIVEL) + 1);
    *(combA+i) = numSorteadoCombA;
    printf("Aviao %d = %d \n",i+1, combA[i]);
  }
  *(vetInformacoes + 0) = nVoos;
  *(vetInformacoes + 1) = nAproximacoes;
  *(vetInformacoes + 2) = nDecolagens;
  return 0;
}

void selecionaCodigosVoos(int *vetInformacoes, char *codVoos[], char *codAproximacoes[],  char *codDecolagens[]){
  int nAproximacoes, nDecolagens;
  nAproximacoes = *(vetInformacoes + 1);
  nDecolagens = *(vetInformacoes + 2);
  printf("\nCodigos dos voos de aproximação");
  for(int i=0; i < nAproximacoes; i++){
    codAproximacoes[i] = codVoos[i];
    printf("\t %s", codAproximacoes[i]);
  }
  printf("\nCodigos dos voos de decolagens");
  for(int i = 0;i < nDecolagens; i++){
    codDecolagens[i] = codVoos[i+(nAproximacoes)];
    printf("\t %s", codDecolagens[i]);
  }
}

Lista* criaLista(Lista *lista){

}

void imprimeResultados(int *vetInformacoes){
  //LIMPA_TELA;
  printf("\n---------------------------------------------------------");
  printf("\nAeroporto Internacional de Brasília");
  printf("\nHora inicial: %d:00", HORAINICIAL);
  printf("\nFila de Pedidos:");
  printf("\nNVoos: %d", *(vetInformacoes + 0));
  printf("\nNAproximações: %d", *(vetInformacoes + 1));
  printf("\nNDecolagens: %d", *(vetInformacoes + 2));
  printf("\n---------------------------------------------------------\n");
}
