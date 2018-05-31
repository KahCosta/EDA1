//Integrantes
//Gabriela Moraes - 16/0006872
//Guilherme Siqueira - 16/0007763
//Kamilla Costa - 16/0010969

#include "funcoes.h"

int sorteiaNumero(int nVoos, int nAproximacoes, int nDecolagens, int *combA){
  int numSorteadoCombA;
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
  return 0;
}
