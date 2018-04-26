#include "funcoes.h"

int main(int argc, char *argv[]){
  // Variaveis
  char indice[2], nomeArquivo[100] = "./", setaIArquivo[100] = "./";
  FILE *arq;
  char *setaArquivo = setaIArquivo;

  /*
  int treinamentoGrass[NUMMAX], treinamentoAsphalt[NUMMAX], testeGrass[NUMMAX], testeAsphalt[NUMMAX];
  int numSorteado;
  sorteiaNumero(treinamentoGrass);
  //ordenaVetor(treinamentoGrass);
  comparaVetor(treinamentoGrass, testeGrass);
  */
  for(int i = 1; i <= FILEMAX; i++){
    converterIntChar(i, indice);
    for(int i = 0; i < FILEMAX; i++){
      nomeArquivo[i] = setaArquivo[i];
    }
    printf("nomeArquivo: %s\t setaArquivo: %s", nomeArquivo, setaArquivo);
    concantenaNomeArquivo(nomeArquivo, GRASSFILE, indice);
    arq = abreArquivo(nomeArquivo);
    //aloca
    //calcula
    //guarda
    fechaArquivo(arq);
  }
  return 0;
}
