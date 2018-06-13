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

int calculateQuantityOfNumbers(FILE *arq){
  int qtdRegistros = 0;
  char detectaRegistro;

  fseek(arq, 0, SEEK_SET);

  while(fread(&detectaRegistro,sizeof(char),1,arq)==1){
    if(detectaRegistro == ' '){
      qtdRegistros++;
    }
  }

  return qtdRegistros;
}

FILE* openArchive(char *fileName){
  FILE *arq;

  arq = fopen(fileName, "r");
  if(arq == NULL){
    printf("Erro ao abrir o arquivo!");
  }

  return arq;
}


void readNumbersFromArchive(FILE *arq, int totalOfNumbersInFile, int *fileNumbers){
  //Declarações

  //Instruções
  rewind(arq);
  printf("Números do arquivo: "); //DEBUGANDO
  for(int i = 0; i < totalOfNumbersInFile; i++){
    fscanf(arq, "%d ", &fileNumbers[i]);
    printf("\t%d", fileNumbers[i]); //DEBUGANDO
  }
  fclose(arq);

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

Arvore* loadTreeFromFile(char *fileName){
  //Declarações
  FILE *arq;
  Arvore *raiz = NULL, *novoNo = NULL;
  int totalOfNumbersInFile, *fileNumbers = NULL;
  //int tamanho; //DEBUGANDO

  //Instruções
  // tamanho = strlen(fileName); //DEBUGANDO
  //printf("\nFileName dentro da função %s e tamanho da string %d", fileName, tamanho); //DEBUGANDO
  arq = openArchive(fileName);
  totalOfNumbersInFile = (calculateQuantityOfNumbers(arq) + 1);
  //printf("\nqtdRegistros: %d\n", totalOfNumbersInFile);//DEBUGANDO
  fileNumbers = calloc(totalOfNumbersInFile, sizeof(int));
  readNumbersFromArchive(arq, totalOfNumbersInFile, fileNumbers);
  for(int i = 0; i < totalOfNumbersInFile; i++){
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
