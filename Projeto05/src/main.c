//Integrantes
//Gabriela Moraes - 16/0006872
//Guilherme Siqueira - 16/0007763
//Kamilla Costa - 16/0010969

#include "funcoes.h"

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "Portuguese");

  //Declaracoes
  int opcao;
  char lock;
  char fileName[15];
  Arvore *raiz = NULL; //Criando arvore vazia

  //Instrucoes
  do{
    opcao = menu();
    switch(opcao){
      case 1:
        LIMPA_TELA;
        concatenateFileName(fileName);
        // printf("\nMain Filename: %s", fileName); //DEBUGANDO
        raiz = loadTreeFromFile(fileName);
        printf("\nWait... Creating Tree\n");
        for(int i = 0; i < 3; i++){
          sleep(1);
          printf("*\n");
        }
        printf("\nSuccessfully created tree... Press ENTER ");
        LIMPA_BUFFER;
        lock = getchar();
      break;

      case 2:
        LIMPA_TELA;
        showTree(raiz);
        printf("\nPress ENTER to comeback to menu ");
        LIMPA_BUFFER;
        lock = getchar();
      break;

      case 3:
        LIMPA_TELA;
        isFull();
      break;

      case 4:
        LIMPA_TELA;
        searchValue();
      break;

      case 5:
        LIMPA_TELA;
        getHeight();
      break;

      case 6:
        LIMPA_TELA;
        removeValue();
      break;

      case 7:
        LIMPA_TELA;
        printInOrder();
      break;

      case 8:
        LIMPA_TELA;
        printPreOrder();
      break;

      case 9:
        LIMPA_TELA;
        printPostOrder();
      break;

      case 10:
        balanceTree();
      break;
    }
  }while(opcao != 0);

  LIMPA_TELA;
  printf("===========================================================");
  printf("\nProgram finished");
  printf("\n===========================================================\n");
  return 0;
}
