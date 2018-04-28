#include "funcoes.h"

int main(int argc, char *argv[]){
  // Variaveis
  char indice[2], nomeArquivo[100] = "./", setaIArquivo[100] = "./";
  FILE *arq;
  int *matriz, tamanhoMatriz, dimMatriz[2], *ilbp;
  char *setaArquivo = setaIArquivo;
  /*
  int treinamentoGrass[NUMMAX], treinamentoAsphalt[NUMMAX], testeGrass[NUMMAX], testeAsphalt[NUMMAX];
  int numSorteado;
  sorteiaNumero(treinamentoGrass);
  //ordenaVetor(treinamentoGrass);
  comparaVetor(treinamentoGrass, testeGrass);
  */
  setlocale(LC_ALL, "Portuguese");
  for(int i = 1; i <= 1/*FILEMAX*/; i++){
    converterIntChar(i, indice);
    for(int i = 0; i < 1/*FILEMAX*/; i++){
      nomeArquivo[i] = setaArquivo[i];
    }
    printf("nomeArquivo: %s\t setaArquivo: %s", nomeArquivo, setaArquivo);
    concantenaNomeArquivo(nomeArquivo, GRASSFILE, indice);
    arq = abreArquivo(nomeArquivo);
    calculaDimensao(arq, dimMatriz);
    tamanhoMatriz = ((*(dimMatriz + 0)) * (*(dimMatriz + 1)));
    matriz = alocaMatriz(tamanhoMatriz);// matriz é o ponteiro da alocação dinamica
    salvaMatrizMemoria(arq, matriz, dimMatriz);
    //calcula
    ilbp = alocaMatriz(512);
    calculaILBP(matriz, ilbp);
    //guarda
    fechaArquivo(arq);
    free(matriz);
    free(ilbp);
  }
  return 0;
}
