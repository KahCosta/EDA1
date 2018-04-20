#include "funcoes.h"

int sorteiaNumero(){
  srand((unsigned) time(NULL));
  for(int i = 0; i < NUMMAX; i++){
    do{
        vetorValido[i] = ((rand() % FILEMAX) + 1);
    }while(validaNumeroSorteado());
    printf("%d",vetorValido[i]);
  }
}

int validaNumeroSorteado(){

}



int sorteiaNumero(){
  int vetorValido[NUMMAX], vetorInvalido[NUMMAX];
  srand((unsigned) time (NULL));
  for(int i = 0; i < NUMMAX; i++){
    do{
      vetorValido[i] = ((rand() % FILEMAX) + 1);// Para ser de 1 a 50
      vetorInvalido[i] = vetorValido[i];

    }while();
    printf("%d\t", vetor[i]);
  }
  //return numSorteado;
}

int validaNumeroSorteado(int numSorteado, int *vetor){
  for(int i = 0; i < NUMMAX; i++){
    if(numSorteado == *(vetor+i)){
      return 1;
    }
    else{
      return 0;
    }
  }
}

void selecionaImagens(int *vetor){
  //Declaraçoes
  int numSorteado;

  for(int i = 0; i < NUMMAX; i++){
    numSorteado = sorteiaNumero();
    printf("\n%d\n", numSorteado);
    printf("\nAAAAAAAAAAAAAAAAAAAAAAAAA\n");

    /*
    while(validaNumeroSorteado(numSorteado, vetor) == 1){
      numSorteado = sorteiaNumero();
    }
    *(vetor+i) = numSorteado;

  }
}
