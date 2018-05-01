#include "funcoes.h"
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

int* alocaMatriz(int tamanho){
  int *matriz;
  matriz = (int *) calloc(tamanho, sizeof(int));
  if(matriz == NULL){
    printf("Alocação falhou!");
    exit(1);
  }
  return matriz;
}

void salvaMatrizMemoria(FILE *arq, int *matriz, int *dimMatriz){
  int nLin = 0, nCol = 0;
  nLin = *(dimMatriz +0);
  nCol = *(dimMatriz + 1);
  char guarda[nLin][nCol];

  printf("\nnLin:%d\tnCol:%d",nLin, nCol);

  rewind(arq);
  for(int i = 0; i < nLin; i++){
    for(int j = 0; j < nCol; j++){
      fscanf(arq, "%d%c", matriz+(i*nCol)+j, &guarda[i][j]);
      printf("\nLinha:%d\tColuna:%d\tConteudo:%d\t",i,j, *(matriz+(i*nCol)+j));
    }
  }
}

void fechaArquivo(FILE *arq){
  fclose(arq);
}

void calculaILBP(int *matriz, int *ilbp){
  int pixel = 0, linhas = 3, colunas = 3, pixelCentral = 0, somatorio = 0, precisaoCalcT = 0, tamanhoMatriz = 0;
  int *matrizBinaria = NULL, numVizinhos = 0;
  float mediaPixelCentral = 0.0;

  //calcula filtro de média (por enquanto só dos primeiros 9 elementos)
  pixelCentral = *(matriz + 4);
  //printf("Pixel Central = %d \n", pixelCentral);
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      printf("Elementos da matriz %d\n", (*(matriz+(i*colunas)+j)));
      somatorio = somatorio + (*(matriz+(i*colunas)+j));
    }
  }
  mediaPixelCentral = somatorio / (9.0);
  *(matriz+4) = mediaPixelCentral;
//  printf("Linhas = %d\n Colunas = %d\n Somatório = %d", linhas, colunas, somatorio );
  printf("\nMedia = %f \n", mediaPixelCentral);

/*Limiarização Simples */
  tamanhoMatriz = linhas * colunas;
  matrizBinaria = alocaMatriz(tamanhoMatriz);
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      if((*(matriz+(i*colunas)+j)) > *(matriz+4)){
        (*(matrizBinaria+(i*colunas)+j)) = 1;
      }else{
        (*(matrizBinaria+(i*colunas)+j)) = 0;
      }
      printf("Matriz Binária: %d\n", (*(matrizBinaria+(i*colunas)+j)));

    }
  }

  //Calcular Menor Binário para invariância de rotação e cálculo do ILBP
  numVizinhos = 8;
  int num = 0; //valor decimal
  int binario[9], aux[9], decimal = 0;
  int numMin = 511; //1024 / (2 -1)
  int res = 0;
  int contador = 0;

  for(int i = 0; i < linhas; i++){
    for(int j = 0; j < colunas; j++, contador++){
      *(binario+contador) = (*(matrizBinaria+(i*colunas)+j));
     // printf("BinarioPrimeiro[%d] = %d\n",j,binario[contador] ); //OK
    }
  }

  for(int i = 0; i < 9; i++, contador++){
   // printf("Binario[%d] = %d\n", i, binario[contador]);
  }

  for (int i = 0; i < 9; i++) { //conversor bin -> dec
    for (int j = 0; j < 9; j++){
      if (binario[j] == 1)
      {
        num += pow(2,8-j);
        printf("j = %d\n",j); 
      }
      //num += binario[j] * pow(2, j);    
      //printf("Bin - Dec = %d\n",num);  
    }
      for (int k = 0; k < numVizinhos; k++){
        aux[k] = *(binario+(k + 1));
      }

      for (int l = 0; l < 9; l++){
        *(binario + l) = aux[l];
       // printf("AAA%d\n",*(matrizBinaria + l) );
      }
        printf("Debug num = %d\n", num);

      if (numMin > num ){
        numMin = num;
        printf("Numero Min = %d\n", numMin );
      }

    for (int j = 0; j < 9; j++){
      if (binario[j] == 1)
      {
        num += pow(2,8-j);
        printf("j = %d\n",j); 
      }
    }

  }
  printf("min Final = %d \n", numMin);

  


  free(matrizBinaria);
}
