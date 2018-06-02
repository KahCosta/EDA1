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
  nAproximacoes = NUMMINAPROXDECOLAGEM + (rand() % NUMMAXAPROXDECOLAGEM);
  if(nAproximacoes > NUMMAXAPROXDECOLAGEM){
    nAproximacoes = nAproximacoes - NUMMINAPROXDECOLAGEM;
  }
  nDecolagens = NUMMINAPROXDECOLAGEM +(rand() % NUMMAXAPROXDECOLAGEM);
  if(nDecolagens > NUMMAXAPROXDECOLAGEM){
    nDecolagens = nDecolagens - NUMMINAPROXDECOLAGEM;
  }

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

Fila* criaFilaAproximacao(Fila* filaAproximacao,int *vetInformacoes, char *codVoos[],
                          char *codAproximacoes[],  char *codDecolagens[], int *combA){

  int nAproximacoes, nDecolagens, nVoos;
  Info* vetAproximacao = NULL;
  nVoos = *(vetInformacoes);
  nAproximacoes = *(vetInformacoes + 1);
  nDecolagens = *(vetInformacoes + 2);

  vetAproximacao = (Info*) malloc(nAproximacoes * sizeof(Info));
  if(vetAproximacao == NULL){
    printf("Alocação falhou!\n");
    exit(2);
  }

  filaAproximacao = (Fila*)malloc(nAproximacoes*sizeof(Fila));
  if(filaAproximacao == NULL){
    printf("Alocação falhou\n");
    exit(2);
  }

  printf("\nCodigos dos voos de aproximação\n");
  for(int i=0; i < nAproximacoes; i++){
    //printf("Teste: %s\n", codVoos[i]);
    strcpy(vetAproximacao[i].codigoVoo,codVoos[i]);
    printf("Código: %s\n", vetAproximacao[i].codigoVoo);
    vetAproximacao[i].status = 'A';
    printf("Status: %c\n", vetAproximacao[i].status);
    vetAproximacao[i].qtdCombustivel = combA[i];
    printf("Combustivel: %d\n\n", vetAproximacao[i].qtdCombustivel);

    filaAproximacao = insereFila(filaAproximacao, vetAproximacao[i]);
  }
}

No* insereFila(Fila* filaAproximacao, Info novoVoo){
  No *inicio, *fim, *aux, *novoElemento;
  novoElemento->info = novoVoo;
  aux = filaAproximacao->inicio;
  if(aux!=NULL){
    while (aux->prox) {
      aux = aux->prox;
    }
    aux->prox = novoElemento;
    filaAproximacao->fim = novoElemento;
    filaAproximacao->fim->prox = NULL;
  }else{
    filaAproximacao->inicio = novoElemento;
    filaAproximacao->fim = novoElemento;
    filaAproximacao->fim->prox = NULL;
  }
  return filaAproximacao;
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
