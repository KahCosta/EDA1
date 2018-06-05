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
  }
  for(int i = 0; i < nAproximacoes; i++){
    printf("Aviao %d = %d \n",i+1, combA[i]);
  }
  *(vetInformacoes + 0) = nVoos;
  *(vetInformacoes + 1) = nAproximacoes;
  *(vetInformacoes + 2) = nDecolagens;
  ordenaPrioridade(combA, nAproximacoes);
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

void ordenaPrioridade( int *vetor, int TAM){
  int x,y;
  int aux;
  for( x = 0; x < TAM; x++ ){
    for( y = x + 1; y < TAM; y++ ){
      if ( vetor[x] > vetor[y] ){
           aux = vetor[x];
           vetor[x] = vetor[y];
           vetor[y] = aux;
        }
      }
    }
  printf("\n\nVetor ordenado\n");
  for(int i = 0; i < TAM; i++){
    printf("%d\t", vetor[i]);
  }
}

Fila* criaFilaAproximacao(){
  Fila *fAprox = (Fila*)malloc(sizeof(Fila));
  fAprox->inicio = NULL;
  fAprox->fim = NULL;

  return fAprox;
}

Fila* criaFilaDecolagem(){

  Fila *fDec = (Fila*)malloc(sizeof(Fila));
  fDec->inicio = NULL;
  fDec->fim = NULL;

  return fDec;
}

void insereFila(Fila *f, char *cod[], char status, int i, int *combA){
  f->fim = insereFinalFila(f->fim, cod, status, i, combA);
  if(f->inicio == NULL){
    f->inicio = f->fim;
  }
}

No* insereFinalFila(No* fim, char *cod[], char status, int i, int *combA){
  No* novoElemento = NULL;
  novoElemento = (No*) malloc(sizeof(No));
  novoElemento->info.status = status;
  strcpy(novoElemento->info.codigoVoo, cod[i]);
  if(status == 'D'){
    novoElemento->info.qtdCombustivel = 12;
  }
  else{
    novoElemento->info.qtdCombustivel = combA[i];
  }
  novoElemento->prox = NULL;
  if(fim != NULL){
    fim->prox = novoElemento;
  }
  return novoElemento;
}

void imprimeFila(Fila *f){
  No* aux;
  for(aux = f->inicio; aux != NULL; aux = aux->prox){
    printf("\n\n\nCódigo do Voo: %s", aux->info.codigoVoo);
    printf("\nStatus: %c", aux->info.status);
    printf("\nQuantidade de combustível: %d", aux->info.qtdCombustivel);

  }
}

Fila* criaFilaPista1(){
  Fila *fPista1 = (Fila*)malloc(sizeof(Fila));
  fPista1->inicio = NULL;
  fPista1->fim = NULL;

  return fPista1;
}

Fila* criaFilaPista2(){
  Fila *fPista2 = (Fila*)malloc(sizeof(Fila));
  fPista2->inicio = NULL;
  fPista2->fim = NULL;

  return fPista2;
}

Fila* criaFilaPista3(){
  Fila *fPista3 = (Fila*)malloc(sizeof(Fila));
  fPista3->inicio = NULL;
  fPista3->fim = NULL;

  return fPista3;
}

No* auxDesenfileiraFila(No* inicio){
  No *p = inicio->prox;
  free(inicio);
  //printf("DESENFILEIROU p = %s\n", p);
  return p;
}

Info desenfileiraFila(Fila *f){
  Info aux;

  if(filaVazia(f)){
    printf("Fila vazia\n");
    exit(2);
  }
  aux = f->inicio->info;
  f->inicio = auxDesenfileiraFila(f->inicio);
  if(f->inicio == NULL){
    f->fim = NULL;
  }
  return aux;
}

int filaVazia (Fila* f)
{
   return (f->inicio==NULL);
}






void insereFilaPista(Fila *pista, No *final){
  No* aux;
    pista->fim = insereFinalFilaPista(pista->fim, final);
    if(pista->inicio == NULL){
      pista->inicio = pista->fim;
    }
}

No* insereFinalFilaPista(No* final, Fila *f){
  No* novoElemento = NULL;
  No* aux = NULL;
  for (aux = f->inicio; aux != NULL; aux = aux->prox) {
    novoElemento = (No*) malloc(sizeof(No));
    novoElemento->info = aux->info;
    novoElemento->prox = NULL;
    if(final != NULL){
      final->prox = novoElemento;
    }
  }
  return novoElemento;
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
