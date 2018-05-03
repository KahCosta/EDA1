#include "funcoes.h"

int main(int argc, char *argv[]){
  // Variaveis
  char indice[2], nomeArquivo[100] = "./", setaIArquivo[100] = "./";
  FILE *arq;
  int tamanhoMatriz, dimMatriz[2];
  int **matriz = NULL, **matrizDireita = NULL, **matrizEsquerda = NULL, **matrizAbaixo = NULL, **matrizAcima = NULL,
      **matrizDireitaInferior = NULL, **ilbp = NULL, **matrizBinaria = NULL, **matrizDireitaSuperior = NULL, **matrizEsquerdaSuperior = NULL, **matrizEsquerdaInferior = NULL;
  char *setaArquivo = setaIArquivo;
  int valorMaior, contador = 0;
  int treinamento[NUMMAX], teste[NUMMAX];
  /*
  int treinamentoGrass[NUMMAX], treinamentoAsphalt[NUMMAX], testeGrass[NUMMAX], testeAsphalt[NUMMAX];
  int numSorteado;
  sorteiaNumero(treinamentoGrass);
  //ordenaVetor(treinamentoGrass);
  comparaVetor(treinamentoGrass, testeGrass);
  */
  setlocale(LC_ALL, "Portuguese");
  for(int i = 0; i < 2; i++){
    for(int i = 1; i <= 1; i++){ //MUDAR PARA FILEMAX
      converterIntChar(i, indice);
      for(int j = 0; j < FILEMAX; j++){
        nomeArquivo[j] = setaArquivo[j];
      }
      printf("nomeArquivo: %s\t setaArquivo: %s", nomeArquivo, setaArquivo);
      if(contador == 1){
        concantenaNomeArquivo(nomeArquivo, ASPHAULTFILE, indice);
      }
      else{
        concantenaNomeArquivo(nomeArquivo, GRASSFILE, indice);
      }
      arq = abreArquivo(nomeArquivo);
      calculaDimensao(arq, dimMatriz);
      tamanhoMatriz = ((*(dimMatriz + 0)) * (*(dimMatriz + 1)));
      printf("Tamanho da matriz: %d\n",tamanhoMatriz );
      matriz = alocaMatriz(dimMatriz);// matriz é o ponteiro da alocação dinamica
      salvaMatrizMemoria(arq, matriz, dimMatriz, &valorMaior);
      printf("\n\nILBP");
      //calculaILBP(matriz, ilbp, dimMatriz, matrizBinaria);
      printf("\n\nGLCM");
      direita(matrizDireita, matriz);
      esquerda(matrizEsquerda, matriz);
      acima(matrizAcima, matriz);
      abaixo(matrizAbaixo, matriz);
      diagonalEsquerdaSuperior(matrizEsquerdaSuperior, matriz);
      diagonalDireitaSuperior(matrizDireitaSuperior, matriz);
      diagonalEsquerdaInferior(matrizEsquerdaInferior, matriz);
      diagonalDireitaInferior(matrizDireitaInferior, matriz);
      fechaArquivo(arq);
      free(matriz);
    }
    contador++;
  }
  sorteiaNumero(treinamento);
  comparaVetor(treinamento, teste);
  return 0;
}
