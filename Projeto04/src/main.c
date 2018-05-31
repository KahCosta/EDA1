//Integrantes
//Gabriela Moraes - 16/0006872
//Guilherme Siqueira - 16/0007763
//Kamilla Costa - 16/0010969

#include "funcoes.h"

int main(int argc, char *argv[]){
  setlocale(LC_ALL, "Portuguese");

  //Declaracoes
  int nVoos = NUMMINVOOS, nAproximacoes = NUMMINAPROXDECOLAGEM, nDecolagens = NUMMINAPROXDECOLAGEM, combA[NUMMAXAPROXDECOLAGEM];

  //Instrucoes
  sorteiaNumero(nVoos, nAproximacoes, nDecolagens, combA);

  return 0;
}
