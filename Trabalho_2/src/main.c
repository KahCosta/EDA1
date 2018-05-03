#include "../inc/funcoes.h"

int main(int argc, char *argv[]){
  // Variaveis
  char indice[2], nomeArquivo[100] = "../", setaIArquivo[100] = "../";
  FILE *arq;
  int **matriz, tamanhoMatriz, dimMatriz[2], **matrizDireita, **matrizEsquerda, **matrizAbaixo, **matrizAcima,
      **matrizDireitaInferior, **matrizDireitaSuperior, **matrizEsquerdaSuperior, **matrizEsquerdaInferior;
  char *setaArquivo = setaIArquivo;
  int valorMaior;

  /*
  int treinamentoGrass[NUMMAX], treinamentoAsphalt[NUMMAX], testeGrass[NUMMAX], testeAsphalt[NUMMAX];
  int numSorteado;
  sorteiaNumero(treinamentoGrass);
  //ordenaVetor(treinamentoGrass);
  comparaVetor(treinamentoGrass, testeGrass);
  */
  setlocale(LC_ALL, "Portuguese");
  // for(int i = 1; i <= FILEMAX; i++){
    int i = 1;
    converterIntChar(i, indice);
    for(int j = 0; j < FILEMAX; j++){
      nomeArquivo[j] = setaArquivo[j];
    }
    printf("nomeArquivo: %s\t setaArquivo: %s", nomeArquivo, setaArquivo);
    concantenaNomeArquivo(nomeArquivo, GRASSFILE, indice);
    arq = abreArquivo(nomeArquivo);
    calculaDimensao(arq, dimMatriz);
    tamanhoMatriz = ((*(dimMatriz + 0)) * (*(dimMatriz + 1)));
    printf("%d\n",tamanhoMatriz );
    matriz = alocaMatriz(tamanhoMatriz);// matriz é o ponteiro da alocação dinamica
    salvaMatrizMemoria(arq, matriz, dimMatriz, &valorMaior);
    direita(matrizDireita, valorMaior, tamanhoMatriz, matriz);
    esquerda(matrizEsquerda, valorMaior, tamanhoMatriz, matriz);
    acima(matrizAcima, valorMaior, tamanhoMatriz, matriz);
    abaixo(matrizAbaixo, valorMaior, tamanhoMatriz, matriz);
    diagonalEsquerdaSuperior(matrizEsquerdaSuperior, valorMaior, tamanhoMatriz, matriz);
    diagonalDireitaSuperior(matrizDireitaSuperior, valorMaior, tamanhoMatriz, matriz);
    diagonalEsquerdaInferior(matrizEsquerdaInferior, valorMaior, tamanhoMatriz, matriz);
    diagonalDireitaInferior(matrizDireitaInferior, valorMaior, tamanhoMatriz, matriz);
    fechaArquivo(arq);
    free(matriz);
  // }
  return 0;
}
