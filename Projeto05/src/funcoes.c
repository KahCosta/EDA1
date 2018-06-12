//Integrantes
//Gabriela Moraes - 16/0006872
//Guilherme Siqueira - 16/0007763
//Kamilla Costa - 16/0010969

#include "funcoes.h"

int menu(){
  //Declarações
  int opcao;

  //Instruções
  LIMPA_TELA;
  printf("==================== TREE PROGRAM =========================");
  printf("\n1 - Load Tree From File");
  printf("\n2 - Show Tree");
  printf("\n3 - Is Full");
  printf("\n4 - Search Value");
  printf("\n5 - Get Height");
  printf("\n6 - Remove Value");
  printf("\n7 - Print In Order");
  printf("\n8 - Print Pre Order");
  printf("\n9 - Print Post Order");
  printf("\n10 - Balance Tree");
  printf("\n0 - Exit");
  do{
    printf("\n\nEnter the number of the function you would like to do: ");
    scanf("%d", &opcao);
  }while(validateNumbers(opcao, 0, 10) == 1);
  return opcao;
}

int validateNumbers(int numberEntered, int min, int max){
  //Declarações

  //Instruções
  while(numberEntered < min || numberEntered > max){
    printf("\nInvalid Number! Try again\n");
    return 1;
  }
  return 0;
}

void concatenateFileName(char *fileName){
  //Declarações
  int fileNumber;
  char strFileName[15] = FILENAME, strFileNumber[2];

  //Instruções
  do{
    printf("Enter the number between 1 and 6 of the file: ");
    LIMPA_BUFFER;
    scanf("%d", &fileNumber);
  } while(validateNumbers(fileNumber, 1, 6) == 1);
  sprintf(strFileNumber, "%d", fileNumber);
  strcat(strFileName, strFileNumber);
  strcat(strFileName, EXTENSION);

  strcpy(fileName, strFileName);
  // printf("fileName %s", fileName); //DEBUGANDO
}

Arvore* createNewNode(int fileNumber){
  //Declarações

  //Instruções
  Arvore *novoNo = (Arvore*) malloc(sizeof(Arvore));
  novoNo->info = fileNumber;
  novoNo->esquerda = NULL;
  novoNo->direita = NULL;

  return novoNo;
}

Arvore* insert(Arvore *raiz, Arvore *novoNo){
  //Declarações

  //Instruções
  if(raiz == NULL){ //arvore vazia
    return novoNo;
  }
  if(raiz->info > novoNo->info){
    raiz->esquerda = insert(raiz->esquerda, novoNo);
  }
  else{
    raiz->direita = insert(raiz->direita, novoNo);
  }

  return raiz;
}

void readNumbersFromArchive(char *fileName, int *fileNumbers){
  //Declarações
  FILE *arq;

  //Instruções
  arq = fopen(fileName, "r");
  if(arq == NULL){
    printf("Erro ao abrir o arquivo!");
  }
  printf("Números do arquivo: "); //DEBUGANDO
  for(int i = 0; i < 10; i++){
    fscanf(arq, "%d ", &fileNumbers[i]);
    printf("\t%d", fileNumbers[i]); //DEBUGANDO
  }
  fclose(arq);

}

Arvore* loadTreeFromFile(char *fileName){
  //Declarações
  Arvore *raiz, *novoNo;
  int fileNumbers[10];

  //Instruções
  readNumbersFromArchive(fileName, fileNumbers);
  for(int i = 0; i < 10; i++){
    novoNo = createNewNode(fileNumbers[i]);
    raiz = insert(raiz, novoNo);
  }

  return raiz;
}

void showTree(Arvore* raiz){
  //Declarações

  //Instruções
  if (!(raiz == NULL)){
    printf("%d\t", raiz->info);
    showTree(raiz->esquerda);
    showTree(raiz->direita);
  }

}

void isFull(){
  //Declarações

  //Instruções
}

void searchValue(){
  //Declarações

  //Instruções
}

void getHeight(){
  //Declarações

  //Instruções
}

void removeValue(){
  //Declarações

  //Instruções
}

void printInOrder(){
  //Declarações

  //Instruções
}

void printPreOrder(){
  //Declarações

  //Instruções
}

void printPostOrder(){
  //Declarações

  //Instruções
}

void balanceTree(){
  //Declarações

  //Instruções
}
