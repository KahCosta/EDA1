//Integrantes
//Gabriela Moraes - 16/0006872
//Guilherme Siqueira - 16/0007763
//Kamilla Costa - 16/0010969

#include "funcoes.h"


Arvore *raiz = NULL;

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "Portuguese");

  //Declaracoes
  int opcao, tamanho, valueSearched, valueDeleted;
  char userFileName[100], *fileName;

  //Instrucoes
  do{
    opcao = menu();
    switch(opcao){
      case 1:
        LIMPA_TELA;
        printf("=============== LOAD TREE =================\n\n");
        printf("Enter the name of the file: ");
        LIMPA_BUFFER;
        fgets(userFileName, 100, stdin);
        tamanho = strlen(userFileName);
        fileName = calloc((tamanho-1), sizeof(char));
        if(fileName == NULL){
          printf("Alocação falhou!");
          exit(1);
        }
        strncpy(fileName, userFileName, (tamanho-1));
        raiz = loadTreeFromFile(fileName);
        free(fileName);

      break;

      case 2:
        LIMPA_TELA;
        printf("=============== SHOW TREE =================\n\n");
        if(isEmpty(raiz) == 1){
          printf("Empty tree");
        }
        else{
          showTree(raiz);
        }
        printf("\n\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 3:
        LIMPA_TELA;
        printf("=============== IS FULL  =================\n\n");
        isFull(raiz);
        printf("\n\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 4:
        LIMPA_TELA;
        printf("=============== SEARCH =================\n\n");
        if(isEmpty(raiz) == 1){
          printf("Empty tree");
        }
        else{
          int height = calculateHeight(raiz);
          printf("Enter the value you would like to search: ");
          scanf("%d", &valueSearched);
          searchValue(raiz, valueSearched,height);
        }
        printf("\n\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 5:
        LIMPA_TELA;
        printf("=============== TREE HEIGHT ==================\n\n");
        getHeight(raiz);
        printf("\n\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 6:
        LIMPA_TELA;
        printf("=============== DELETE =================\n\n");
        if(isEmpty(raiz) == 1){
          printf("Empty tree");
        }
        else{
          int height = calculateHeight(raiz);
          printf("Enter the value you would like to delete: ");
          scanf("%d", &valueDeleted);
          if(searchValue(raiz, valueDeleted, height) != -1){
            raiz = removeValue(raiz, valueDeleted);
            printf("\n\nWait... Deleting Node\n");
            for(int i = 0; i < 3; i++){
              sleep(1);
              printf("*\n");
            }
            printf("\nSuccessfully Deleted node...");
          }
        }
        printf("\n\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 7:
        LIMPA_TELA;
        printf("=============== IN ORDER ==================\n\n");
        if(isEmpty(raiz) == 1){
          printf("Empty tree");
        }
        else{
          printInOrder(raiz);
        }
        printf("\n\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 8:
        LIMPA_TELA;
        printf("=============== PRE ORDER ==================\n\n");
        if(isEmpty(raiz) == 1){
          printf("Empty tree");
        }
        else{
          printPreOrder(raiz);
        }
        printf("\n\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 9:
        LIMPA_TELA;
        printf("=============== POST ORDER ==================\n\n");
        if(isEmpty(raiz) == 1){
          printf("Empty tree");
        }
        else{
          printPostOrder(raiz);
        }
        printf("\n\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        getchar();
      break;

      case 10:
        LIMPA_TELA;
        printf("=============== BALANCE ==================\n\n");
        raiz = balanceTree(raiz);
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
