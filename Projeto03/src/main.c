//Integrantes
//Gabriela Moraes - 16/0006872
//Guilherme Siqueira - 16/0007763
//Kamilla Costa - 16/0010969

#include "funcoes.h"

int main(int argc, char *argv[]){
  setlocale(LC_ALL, "Portuguese");

  //Variaveis
  FILE *arq;
  int opcao, qtdRegistros;
  contato novoContato;
  No *lista = NULL;//Referencia da lista

  //Instruções
  arq = abreArquivo(NOMEARQUIVO);
  darBoasVindas();
  qtdRegistros = calculaQtdRegistros(arq);
  lista = leArquivo(arq, qtdRegistros, lista);
  fclose(arq);
  LIMPA_TELA;
  do{
    opcao = menu();
    switch(opcao){
        case SAIR:
          arq = fopen(NOMEARQUIVO, "w+");
          escreveArquivo(lista, arq);
          fclose(arq);
          //liberarLista(lista);
          LIMPA_TELA;
          printf("================================================");
          printf("\n\nPrograma finalizado com sucesso!\n\n");
          printf("================================================\n");
          break;
        case INSERIR:
          novoContato = insereDadosContato();
          lista = insereLista(lista, novoContato);
          break;
        case REMOVER:
          lista = excluiElemento(lista);
          break;
        case VISUALIZARNOME:
          pesquisaElemento(lista);
          break;
        case VISUALIZARORDEMALFABETICA:
          imprimeLista(lista);
          break;
    }
  }while(opcao != SAIR);

  return 0;
}
