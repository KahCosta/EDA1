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

  return arq;
}


void readNumbersFromArchive(FILE *arq, int totalOfNumbersInFile, int *fileNumbers){
  //Declarações

  //Instruções
  rewind(arq);
  //printf("Números do arquivo: "); //DEBUGANDO
  for(int i = 0; i < totalOfNumbersInFile; i++){
    fscanf(arq, "%d ", &fileNumbers[i]);
    //printf("\t%d", fileNumbers[i]); //DEBUGANDO
  }

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
  if(raiz == NULL){
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
  if(arq == NULL){
    printf("Cannot open file!");
    printf("\nPress ENTER to comeback to menu ");
    LIMPA_BUFFER;
    getchar();
  }else{
    totalOfNumbersInFile = (calculateQuantityOfNumbers(arq) + 1);
    //printf("\nqtdRegistros: %d\n", totalOfNumbersInFile);//DEBUGANDO
    fileNumbers = calloc(totalOfNumbersInFile, sizeof(int));
    readNumbersFromArchive(arq, totalOfNumbersInFile, fileNumbers);
    fclose(arq);
    for(int i = 0; i < totalOfNumbersInFile; i++){
      novoNo = createNewNode(fileNumbers[i]);
      raiz = insert(raiz, novoNo);
    }
    printf("\n\nWait... Creating Tree\n");
    for(int i = 0; i < 3; i++){
      sleep(1);
      printf("*\n");
    }
    printf("\nSuccessfully created tree... Press ENTER ");
    LIMPA_BUFFER;
    getchar();
  }

  return raiz;
}

int isEmpty(Arvore *raiz){
  //Declarações

  //Instruções
  if(raiz == NULL){
    return 1;
  }
  return 0;
}
//Função de printar 2D do link https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void print2DUtil(Arvore *raiz, int space){
    // Base case
    if (raiz == NULL)
        return;

    // Increase distance between levels
    space += 10;


    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++){
      printf("-");
    }
    printf("%d\n", raiz->info);

    // Process right child first
    print2DUtil(raiz->direita, space);
    // Process left child
    print2DUtil(raiz->esquerda, space);
}

//Função de printar 2D do link https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
// Wrapper over print2DUtil()
void print2D(Arvore *raiz){
   // Pass initial space count as 0
   print2DUtil(raiz, 0);
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

int checkIsFull(Arvore *raiz){
  //Declarações

  //Instruções
  if(raiz == NULL){
    return 2;//verdadeiro
    //0 filhos
  }
  if(raiz->esquerda == NULL && raiz->direita == NULL){
    return 1;//0 filhos
  }
  if((raiz->esquerda) && (raiz->direita)){ //nao for null
    return (checkIsFull(raiz->esquerda) && checkIsFull(raiz->direita));
  }
  return 0;
}

void isFull(Arvore *raiz){
  //Declarações

  //Instruções
  if(checkIsFull(raiz) == 1){
      printf("Tree is full");
  }
  else if(checkIsFull(raiz) == 2){
    printf("Empty Tree");
  }
  else{
      printf("Tree is not full");
  }
}


void searchValue(Arvore *raiz, int value){
  //Declarações

  //Instruções
  if (!(raiz == NULL)){
    if(value == raiz->info){
      printf("\n\nFatherless node\n\n");
      return;
    }else if((raiz->esquerda != NULL) && value < raiz->info){
      if(raiz->esquerda->info == value){
        printf("\n\nDad: %d\n",raiz->info);
        if(!(raiz->direita == NULL)){
          printf("Brother: %d\n\n", raiz->direita->info);
        }
        else{
          printf("\n\nThis node doesn't have brother\n\n");
        }
        return;
      }
      searchValue(raiz->esquerda, value);
    }else if((raiz->direita != NULL)){
      if(raiz->direita->info == value){
        printf("\n\nDad: %d\n",raiz->info);
        if(!(raiz->esquerda == NULL)){
        printf("Brother: %d\n", raiz->esquerda->info);
      }
      else{
        printf("\n\nThis node doesn't have brother\n\n");
      }
        return;
      }
      searchValue(raiz->direita, value);
    }else{
      printf("\n\nNode not found in the tree\n\n");
    }
  }
}

int calculateHeight(Arvore *raiz){
  //Declarações
  int hEsq, hDir, altura;
  //Instruções
  if (raiz == NULL){
    return 0;
  }
  hEsq = calculateHeight(raiz->esquerda);
  hDir = calculateHeight(raiz->direita);
  altura = hEsq > hDir ? hEsq + 1 : hDir + 1;

  return altura;
}

void getHeight(Arvore *raiz){
  //Declarações
  //Instruções
  if(calculateHeight(raiz) == 0){
    printf("Empty tree");
  }
  else{
    printf("Tree Height: %d", calculateHeight(raiz));
  }
}

void removeValue(Arvore *raiz, int valueDeleted){
  //Declarações

  //Instruções
}

void printInOrder(Arvore* raiz){
  //Declarações

  //Instruções
  if (!(raiz == NULL)){
    printInOrder(raiz->esquerda);
    printf("%d\t", raiz->info);
    printInOrder(raiz->direita);
  }
}

void printPreOrder(Arvore* raiz){
  //Declarações

  //Instruções
  if (!(raiz == NULL)){
    printf("%d\t", raiz->info);
    printPreOrder(raiz->esquerda);
    printPreOrder(raiz->direita);
  }

}

void printPostOrder(Arvore* raiz){
  //Declarações

  //Instruções
  if (!(raiz == NULL)){
    printPostOrder(raiz->esquerda);
    printPostOrder(raiz->direita);
    printf("%d\t", raiz->info);
  }
}


int calculateBalanceFactor(Arvore *no){
  //Declarações
  int bf = 0;

  //Instruções
  if(no->esquerda){
    bf += calculateHeight(no->esquerda);
  }
  if(no->direita){
    bf -= calculateHeight(no->direita);
  }

	return bf;
}

Arvore* rotateLeftLeft(Arvore *no){
  //Declarações
  Arvore *a = no;
  Arvore *b = a->esquerda;

  //Instruções
	a->esquerda = b->direita;
	b->direita = a;

	return b;
}

Arvore* rotateLeftRight(Arvore *no){
  //Declarações
  Arvore *a = no;
  Arvore *b = a->esquerda;
  Arvore *c = b->direita;

  //Instruções
	a->esquerda = c->direita;
	b->direita = c->esquerda;
	c->esquerda = b;
	c->direita = a;

	return c;
}

Arvore* rotateRightLeft(Arvore *no){
  //Declarações
  Arvore *a = no;
  Arvore *b = a->direita;
  Arvore *c = b->esquerda;

  //Instruções
	a->direita = c->esquerda;
	b->esquerda = c->direita;
	c->direita = b;
	c->esquerda = a;

	return c;
}

Arvore* rotateRightRight(Arvore *no){
  //Declarações
  Arvore *a = no;
  Arvore *b = a->direita;

  //Instruções
	a->direita = b->esquerda;
	b->esquerda = a;

	return b;
}

Arvore* balanceNode(Arvore *no, Arvore *raiz){
  //Declarações
  Arvore *newroot = NULL;

  //Instruções
	if(no->esquerda){
		no->esquerda  = balanceNode(no->esquerda, raiz);
  }

  if(no->direita){
		no->direita = balanceNode(no->direita, raiz);
  }

	int bf = calculateBalanceFactor(no);

	if(bf >= 2){
		if(calculateBalanceFactor(no->esquerda) <= -1){
      printf("\nRotação Left Right\t");
			newroot = rotateLeftRight(no);
      printInOrder(raiz);
		}
    else{
      printf("\nRotação Left Left\t");
			newroot = rotateLeftLeft(no);
      printInOrder(raiz);
    }
	}
  else if(bf <= -2){

		if(calculateBalanceFactor(no->direita) >= 1){
      printf("\nRotação Right Left\t");
			newroot = rotateRightLeft(no);
      printInOrder(raiz);
		}
    else{
      printf("\nRotação Right Right\t");
			newroot = rotateRightRight(no);
      printInOrder(raiz);
    }
	}
  else {
		newroot = no;
	}

	return newroot;
}

void balance(Arvore *raiz) {
  //Declarações
  Arvore *newroot = NULL;

  //Instruções
	newroot = balanceNode(raiz, raiz);

	if(newroot != raiz){
		raiz = newroot;
	}
}

void balanceTree(Arvore *raiz){
  //Declarações

  //Instruções
  switch(checkIfTreeIsBalanced(raiz)){
    case 0:
      printf("Tree is not balanced");
      balance(raiz);
      printf("\n\nWait... Balancing Tree\n");
      for(int i = 0; i < 3; i++){
        sleep(1);
        printf("*\n");
      }
      printf("\nSuccessfully balanced tree...");
    break;
    case 1:
    printf("Balanced Tree");
    break;
    case 2:
      printf("Empty Tree");
    break;
  }
}

int checkIfTreeIsBalanced(Arvore *raiz) {
  //Declarações
  int value;

  //Instruções
  if (raiz == NULL){
    return 2;
  }
  value = abs(calculateHeight(raiz->direita) - calculateHeight(raiz->esquerda)) <= 1;
  if(checkIfTreeIsBalanced(raiz->direita) == 0 && checkIfTreeIsBalanced(raiz->esquerda) == 0){
    value = 0;
  }
  return value;
}
