#include "funcoes.h"

int sorteiaNumero(){
  int numSorteado, vetor[NUMMAX] = {51}, situacao;

  srand((unsigned) time(NULL));
  for(int i = 0; i < NUMMAX; i++){
    do{
      numSorteado = ((rand() % FILEMAX) + 1);
      situacao = NREPETIDO;
      for(int aux = 0; aux < NUMMAX; aux++){
        if(numSorteado == vetor[aux]){
            situacao = REPETIDO;
        }
      }
    }while(situacao == REPETIDO);
    vetor[i] = numSorteado;
    printf("%d  ", vetor[i]);
  }
}
