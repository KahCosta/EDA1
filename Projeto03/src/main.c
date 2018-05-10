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
  No *lista;//Referencia da lista

  //Instruções
  arq = abreArquivo(NOMEARQUIVO);
  if(arq == NULL){
    printf("Erro  ao abrir o arquivo!");
    exit(1);
  }
  darBoasVindas();
  qtdRegistros = calculaQtdRegistros(arq);
  leArquivo(arq, qtdRegistros);
  /*
  do{
    opcao = menu();
    switch(opcao){
        case SAIR:
          LIMPA_TELA;
          printf("================================================");
          printf("\n\nPrograma finalizado com sucesso!\n\n");
          printf("================================================\n");
          break;
        case INSERIR:
          novoContato = insereDadosContato();
          lista = insereInicioLista(lista, novoContato);
          break;
        case REMOVER:
          break;
        case VISUALIZARNOME:
          break;
        case VISUALIZARORDEMALFABETICA:
          break;
        default:
          LIMPA_TELA;
          printf("\nOpção inválida! Por favor, digite novamente\n\n");
          break;
    }
  }while(opcao != SAIR);
  */
  return 0;
}
