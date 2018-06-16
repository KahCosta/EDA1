//Integrantes
//Gabriela Moraes - 16/0006872
//Guilherme Siqueira - 16/0007763
//Kamilla Costa - 16/0010969

#include "funcoes.h"

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "Portuguese");

  //Declaracoes
  int opcao, tamanho, valueSearched, valueDeleted;
  char userFileName[100], *fileName;
  Arvore *raiz = NULL; //Criando arvore vazia

  //Instrucoes
  do{
    opcao = menu();
    switch(opcao){
      case 1:
        LIMPA_TELA;

        printf("Enter the name of the file: ");
        LIMPA_BUFFER;
        fgets(userFileName, 100, stdin);
        tamanho = strlen(userFileName);// Conta o terminador
        /* DEBUGANDO
        printf("\nName entered by user: %s", userFileName); //DEBUGANDO
        printf("tamanho %d\t", tamanho); //DEBUGANDO
        */
        fileName = calloc((tamanho-1), sizeof(char));
        strncpy(fileName, userFileName, (tamanho-1));
        //printf("fileName %s", fileName); //DEBUGANDO
        raiz = loadTreeFromFile(fileName);

        free(fileName);

      break;

      case 2:
        LIMPA_TELA;
        if(isEmpty(raiz) == 1){
          printf("Empty tree");
        }
        else{
          printf("Show tree\t");
          showTree(raiz);
          printf("\n\nGraficamente");
          print2D(raiz);
        }
        printf("\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 3:
        LIMPA_TELA;
        isFull(raiz);
        printf("\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 4:
        LIMPA_TELA;
        printf("Enter the value you would like to search: ");
        scanf("%d", &valueSearched);
        searchValue(raiz, valueSearched);
        printf("\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 5:
        LIMPA_TELA;
        getHeight(raiz);
        printf("\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 6:
        LIMPA_TELA;
        printf("Enter the value you would like to delete: ");
        scanf("%d", &valueDeleted);
        removeValue(raiz, valueDeleted);
      break;

      case 7:
        LIMPA_TELA;
        if(isEmpty(raiz) == 1){
          printf("Empty tree");
        }
        else{
          printInOrder(raiz);
        }
        printf("\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 8:
        LIMPA_TELA;
        if(isEmpty(raiz) == 1){
          printf("Empty tree");
        }
        else{
          printPreOrder(raiz);
        }
        printf("\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 9:
        LIMPA_TELA;
        if(isEmpty(raiz) == 1){
          printf("Empty tree");
        }
        else{
          printPostOrder(raiz);
        }
        printf("\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 10:
        LIMPA_TELA;
        balanceTree(raiz);
        printf("\n\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;
    }
  }while(opcao != 0);

  LIMPA_TELA;
  printf("===========================================================");
  printf("\nProgram finished");
  printf("\n===========================================================\n");
  return 0;
}
