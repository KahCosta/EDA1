#include "../inc/funcoes.h"
#include <math.h>
/*
int sorteiaNumero(int *treinamentoGrass){
  int numSorteado, vetor[NUMMAX] = {51}, situacao;
  FILE *arq;
  srand((unsigned) time(NULL));
  printf("Conjunto de Treinamento: \n");
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
    treinamentoGrass[i] = vetor[i];
    printf("%d ", treinamentoGrass[i]);
    abreArquivo(arq, numSorteado);
  }
  printf("\n\n");
}
int comparaVetor(int *treinamentoGrass, int *testeGrass){
  int vetorCompara[FILEMAX] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
                              26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50};
  int j=0;
  int comparador = 0;
  int vet[NUMMAX];
  int soma = 0;
  FILE *arq;
  for(int i = 0; i < FILEMAX; i++){
      soma=0;
      comparador = vetorCompara[i];//pega um valor e do vetor de 50 posições e vê se ele existe em treinamentoGrass
    for(int aux = 0; aux < NUMMAX; aux++){
      if(comparador != *(treinamentoGrass + aux)){
        soma++; //Só vê se o valor não existe em treinamentoGrass
      }else{
        vet[aux] = comparador; //se já existe no vetor de treinamento ele guarda num vetor qualquer
        break;
      }
    }
      if(soma == 25 ){ //se entrou nesse if é porque percorreu todo o vetor de treinamento e não encontrou nenhum
                        //valor igual ao do vetor compara
        testeGrass[j] = comparador; //usa j porque se não, na vez que o comparador existir em treinamentoGrass,
        j++;
          if(j==25) //Como o for mais externo vai até 50 e testeGrass tem tamanho 25, tem que testar j<25
            break;
      }
  }
  printf("Conjunto de Teste: \n");
  for (int j=0; j<NUMMAX; j++) {
    printf("%d ", testeGrass[j]);
    abreArquivo(arq, comparador);
  }
  puts("");
}
void abreArquivo(FILE *arq, int num){
  int i;
  char arquivo[29]; //29 é o numero de caracteres do caminho d arq de grama
  if(num < 10)
    snprintf(arquivo, sizeof(arquivo), "%s0%d%s", "./DataSet/grass/grass_", num, EXTENSION);
  else
    snprintf(arquivo, sizeof(arquivo), "%s%d%s", "./DataSet/grass/grass_", num, EXTENSION);
   if((arq=fopen(arquivo,"rt"))==NULL){
       puts("Não foi encontrado registro ");
       getchar();
    }
    leArquivo(arq);
    fechaArquivo(arq);
}
void leArquivo(FILE *arq){
  char detectorPonto;
  int contLinha = 0, contColuna = 0;
  fseek(arq, 0, SEEK_SET);
  while(fread(&detectorPonto,sizeof(char),1,arq)==1){
    if(detectorPonto == '\n'){
      contLinha++;
      contColuna++;
    }
    if(detectorPonto == ';'){
      contColuna++;
    }
  }
  contColuna/=contLinha; //divisão
  printf("%d ", contLinha);
  printf("%d\n", contColuna);
}
*/
void converterIntChar(int i, char *indice){
  sprintf(indice,"%02d", i);
}

void concantenaNomeArquivo(char *nomeArquivo, char *define, char *indice){

  strcat(nomeArquivo, define);
  strcat(nomeArquivo, indice);
  strcat(nomeArquivo, EXTENSION);
  printf("\nFunção\t%s\n", nomeArquivo);
}

FILE* abreArquivo(char *nomeArquivo){
  FILE* arq;

  arq = fopen(nomeArquivo, "r");
  if(arq == NULL){
		printf("Erro ao abrir o arquivo!");
    exit(1);
	}

  return arq;
}

void calculaDimensao(FILE *arq, int *dimMatriz){
  char detectorPonto;
  int contLinha = 0, contColuna = 0;
  fseek(arq, 0, SEEK_SET);

  while(fread(&detectorPonto,sizeof(char),1,arq)==1){
    if(detectorPonto == '\n'){
      contLinha++;
      contColuna++;
    }
    if(detectorPonto == ';'){
      contColuna++;
    }
  }
  contColuna/=contLinha; //divisão
  *(dimMatriz + 0) = contLinha;
  *(dimMatriz + 1) = contColuna;
  printf("%d ", contLinha);
  printf("%d\n", contColuna);
}

int** alocaMatriz(int tamanho){
  int **matriz;
  matriz = (int**)calloc(tamanho,sizeof(int*));
  for(int i=0;i<tamanho;i++){
    *(matriz+i) = calloc(tamanho,sizeof(int));
  }
  return matriz;
}

void salvaMatrizMemoria(FILE *arq, int **matriz, int *dimMatriz, int *valorMaior){
  int nLin = 0, nCol = 0;
  nLin = *(dimMatriz +0);
  nCol = *(dimMatriz + 1);
  char guarda[nLin][nCol];
  int tempValorMaior = 0;

  printf("\nnLin:%d\tnCol:%d",nLin, nCol);

  rewind(arq);
  for(int i = 0; i < nLin; i++){
    for(int j = 0; j < nCol; j++){
      fscanf(arq, "%d%c", &matriz[(i*nCol)][j], &guarda[i][j]);
      printf("\nLinha:%d\tColuna:%d\tConteudo:%d\t",i,j, (matriz[(i*nCol)][j]));
      if((matriz[(i*nCol)][j]) > tempValorMaior){
          tempValorMaior = (matriz[(i*nCol)][j]);
      }
    }
  }
  *valorMaior = tempValorMaior;
}

void CalculaMatrizAux(int valorMaior, int **matriz, int tamanhoMatriz, int posicaoInicial){
  int **matrizAux,i,j;
  int direcao, vet[3];
  matrizAux = (int**)calloc(valorMaior,sizeof(int*));
  for(i=0;i<valorMaior;i++){
    *(matrizAux+i) = calloc(valorMaior,sizeof(int));
  }
  for(direcao = 0; direcao <= 7; direcao++){
    switch(direcao){
        case 0:  // "direita"
          for(i=0;i<tamanhoMatriz;i++){
             for(j=1;j<tamanhoMatriz;j++){
                matrizAux[matriz[i][j-1]][matriz[i][j]]++;
             }
          }
          break;

        case 1:    //"esquerda"
          for(i=0;i<tamanhoMatriz;i++){
             for(j=0;j<(tamanhoMatriz-1);j++){
                matrizAux[matriz[i][j+1]][matriz[i][j]]++;
             }
          }
          break;

        case 2:   //"abaixo"
          for(i=1;i<tamanhoMatriz;i++){
             for(j=0;j<tamanhoMatriz;j++){
                matrizAux[matriz[i-1][j]][matriz[i][j]]++;
             }
          }
          break;

        case 3:  //"acima"
          for(i=0;i<(tamanhoMatriz-1);i++){
             for(j=0;j<tamanhoMatriz;j++){
                matrizAux[matriz[i+1][j]][matriz[i][j]]++;
             }
          }
          break;

        case 4:  //"diagonalEsquerdaInferior"
          for(i=1;i<tamanhoMatriz;i++){
             for(j=0;j<(tamanhoMatriz-1);j++){
                matrizAux[matriz[i-1][j+1]][matriz[i][j]]++;
             }
          }
          break;

        case 5:  //"diagonalEsquerdaSuperior"
          for(i=0;i<(tamanhoMatriz-1);i++){
             for(j=0;j<(tamanhoMatriz-1);j++){
                matrizAux[matriz[i+1][j+1]][matriz[i][j]]++;
             }
          }
          break;

        case 6:  //"diagonalDireitaSuperior"
          for(i=0;i<(tamanhoMatriz-1);i++){
             for(j=1;j<tamanhoMatriz;j++){
                matrizAux[matriz[i+1][j-1]][matriz[i][j]]++;
             }
          }
          break;

        case 7:  //"diagonalDireitaInferior"
          for(i=1;i<tamanhoMatriz;i++){
             for(j=1;j<tamanhoMatriz;j++){
                matrizAux[matriz[i-1][j-1]][matriz[i][j]]++;
             }
          }
          break;
    }
  }

  float contraste=0,energia=0,homogenidade=0;

   for(i=0;i<valorMaior;i++){
       for(j=0;j<valorMaior;j++){

           energia += pow(matrizAux[i][j],2);
           contraste += pow(i-j,2) * matrizAux[i][j];
           homogenidade += matrizAux[i][j]/(1+sqrt(pow(i-j,2)));

         }
       }

 vet[posicaoInicial] = contraste;
 vet[posicaoInicial+1] = energia;
 vet[posicaoInicial+2] = homogenidade;

   for(i=0;i<valorMaior;i++){

        free(matrizAux[i]);

       }
        free(matrizAux);
}
void VetorGLCM(int tamanhoMatriz, int **matriz, int valorMaior){

  int i;
  int posicaoInicial=512;
  int direcao=0;

  for(i=0;i<8;i++){

     CalculaMatrizAux(valorMaior, matriz, tamanhoMatriz, posicaoInicial+i);
     posicaoInicial += 3;
  }
}

void fechaArquivo(FILE *arq){
  fclose(arq);
}
