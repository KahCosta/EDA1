//Integrantes
//Gabriela Moraes - 16/0006872
//Guilherme Siqueira - 16/0007763
//Kamilla Costa - 16/0010969

#include "funcoes.h"

//Implementação das funções
FILE* abreArquivo(char *nomeArquivo){
  //Variaveis
  FILE* arq;

  //Instruções
  arq = fopen(nomeArquivo, "r+");
  if(arq == NULL){
    printf("Erro  ao abrir o arquivo!");
    exit(1);
  }
  return arq;
}

void darBoasVindas(){
  //Variaveis

  //Instruções
  LIMPA_TELA;
  printf("Seja bem vindo a Agenda Pessoal");
  printf("\nEstamos carregando seus contatos... Por favor, aguarde =)\n");
  for(int i = 0; i < 4; i++){
    sleep(1);
    printf(".\n");
  }
}

int menu(){
  //Variaveis
  int opcao;

  //Instruções
  LIMPA_TELA;
  printf("Escolha a operação que deseja realizar na agenda:");
  printf("\n1 - Inserir novo contato");
  printf("\n2 - Remover registro");
  printf("\n3 - Visualizar contatos por nome");
  printf("\n4 - Visualizar contatos em ordem alfabetica");
  printf("\n0 - Sair");
  printf("\n\n\nDigite aqui o número correspondente a operação: ");
  LIMPA_BUFFER;
  scanf("%d", &opcao);

  return opcao;
}

int calculaQtdRegistros(FILE *arq){
  //Variaveis
  int qtdRegistros = 0;
  char detectaRegistro;

  //Instruções
  fseek(arq, 0, SEEK_SET);

  while(fread(&detectaRegistro,sizeof(char),1,arq)==1){
    if(detectaRegistro == '$'){
      qtdRegistros++;
    }
  }
  printf("qtdRegistros: %d\n", qtdRegistros);
  return qtdRegistros;
}

void entradaString(char *string, int tamanho){
  //Variaveis
  int penultimo;

  //Instruções
  LIMPA_BUFFER;
	fgets(string, tamanho, stdin);
  penultimo = strlen(string) - 1;
	if(string[penultimo] == '\n'){
		string[penultimo] = '\0';
	}
}


void leLinha(char *string, int tamanho, FILE *arq){
  //Variaveis
  int penultimo;

  //Instruções
	fgets(string, tamanho, arq);
	penultimo = strlen(string) - 1;
	if(string[penultimo] == '\n'){
		string[penultimo] = '\0';
	}
}

No* leArquivo(FILE *arq, int qtdRegistros, No* lista){
  //Variaveis
  char cep[8];
  fpos_t position;
  contato *contatosExistentes = NULL;

  //Instruções
  contatosExistentes = (contato *) malloc(qtdRegistros * sizeof(contato));
  if(contatosExistentes == NULL){
    printf("\nAlocação falhou!");
    exit(2);
  }
  rewind(arq);
  for(int registro = 0; registro < (qtdRegistros*6); registro+=6){
    fsetpos (arq, &position);
    for(int linha = 1; linha <= 6; linha++){
      if(linha == 1){
        leLinha(contatosExistentes[registro].nomeCompleto, MAXNOMEENDERECO, arq);
      }
      if(linha == 2){
        leLinha(contatosExistentes[registro].telefone, MAXTELEFONEDATA, arq);
      }
      if(linha == 3){
        leLinha(contatosExistentes[registro].endereco, MAXNOMEENDERECO, arq);
      }
      if(linha == 4){
        leLinha(cep, MAXNOMEENDERECO, arq);
        contatosExistentes[registro].cep = atoi(cep);
      }
      if(linha == 5){
        leLinha(contatosExistentes[registro].dataNascimento, MAXTELEFONEDATA, arq);
      }
      if(linha == 6){
        leLinha(contatosExistentes[registro].cifrao, MAXNOMEENDERECO, arq);
        fgetpos (arq, &position);
      }
    }

    lista = insereLista(lista, contatosExistentes[registro]);
    printf("\nNome: %s", contatosExistentes[registro].nomeCompleto);
    printf("\nTelefone: %s", contatosExistentes[registro].telefone);
    printf("\nEndereço: %s", contatosExistentes[registro].endereco);
    printf("\nCep: %u", contatosExistentes[registro].cep);
    printf("\nData Nascimento: %s", contatosExistentes[registro].dataNascimento);
    printf("\nCifrão: %s\n", contatosExistentes[registro].cifrao);

  }
  free(contatosExistentes);
  return lista;
}

void validaNome(char *nome) {
  //Instruções
  while(strlen(nome) < 3 || strstr(nome, " ") == NULL){
    printf("\nNome inválido.");
		printf("\nNome completo (MAX: %d): ", (MAXNOMEENDERECO - 1));
    entradaString(nome, MAXNOMEENDERECO);
  }
}

void validaTelefone(char *telefone){
  //Variaveis

  //Instruções
  while(telefone[5] != '-' || strlen(telefone) < 10){//(MAXTELEFONEDATA - 1)){
    printf("\nFormato inválido.");
    printf("\nTelefone (FORMATO: xxxxx-xxxx): ");
    entradaString(telefone, MAXTELEFONEDATA);
  }
}


void validaDataNascimento(char *dataNascimento){
  //Variaveis

  //Instruções
  while(dataNascimento[2] != '/' || dataNascimento[5] != '/' || strlen(dataNascimento) < 10){//(MAXTELEFONEDATA - 1)){
    printf("\nFormato inválido.");
    printf("\nData de nascimento (FORMATO: dd/mm/aaaa): ");
    entradaString(dataNascimento, MAXTELEFONEDATA);
  }
}

void validaOpcao(char opcao){
  //Variaveis

  //Instruções
  while(opcao != 'n' && opcao != 's'){
    printf("\nOpção inválida! Digite novamente");
    printf("\nConfirma os dados do novo contato? (s/n): ");
    LIMPA_BUFFER;
    opcao = getchar();
    opcao = tolower(opcao);
  }
}

contato insereDadosContato(){
  //Variaveis
  contato novoContato;
  char opcao;

  //Instruções
  do{
    LIMPA_TELA;
    printf("ADICIONAR NOVO CONTATO");
    printf("\nNome completo (MAX: %d): ", (MAXNOMEENDERECO - 1));
    entradaString(novoContato.nomeCompleto, MAXNOMEENDERECO);
    validaNome(novoContato.nomeCompleto);
    printf("\nTelefone (FORMATO: xxxxx-xxxx): ");
    entradaString(novoContato.telefone, MAXTELEFONEDATA);
    validaTelefone(novoContato.telefone);
    printf("\nEndereço (MAX: %d): ", (MAXNOMEENDERECO - 1));
    entradaString(novoContato.endereco, MAXNOMEENDERECO);
    printf("\nCEP: ");
    LIMPA_BUFFER;
    scanf("%u", &novoContato.cep);
    printf("\nData de nascimento (FORMATO: dd/mm/aaaa): ");
    entradaString(novoContato.dataNascimento, MAXTELEFONEDATA);
    validaDataNascimento(novoContato.dataNascimento);
    novoContato.cifrao[0] = '$';
    printf("\n\n\nConfirma os dados do novo contato? (s/n): ");
    LIMPA_BUFFER;
    opcao = getchar();
    opcao = tolower(opcao);
    validaOpcao(opcao);
  }while(opcao == 'n');

  return novoContato;
}

No* insereLista(No* lista, contato novoContato){
    //Variaveis
    No *novoElemento;
    No *aux;
    No* anterior = NULL;// ponteiro q aponta sempre pro anterior ao aux

    //Instruções
    aux = lista;
    novoElemento = (No*) malloc(sizeof(No));
    if(novoElemento == NULL){
      printf("\nAlocação falhou!");
      exit(2);
    }

    novoElemento->conteudo = novoContato;

    if(lista == NULL){
        novoElemento->proximo = NULL;
        novoElemento->anterior = NULL;
        lista = novoElemento;
    }
    else{
      while(aux != NULL && (strcmp(aux->conteudo.nomeCompleto, novoContato.nomeCompleto) < 0)){
        anterior = aux;
        aux = aux->proximo;
      }

        novoElemento->proximo = aux;

      if(anterior == NULL){ // inserindo na primeira posição
        novoElemento->anterior = NULL;
        lista = novoElemento;
      }
      else{
        novoElemento->anterior = anterior;
        anterior->proximo = novoElemento;
      }
      if(aux != NULL){
        aux->anterior = novoElemento;
      }
    }

    return lista;
}

void imprimeLista(No *lista){
  //Variaveis
  No *aux;

  //Instruções
  aux = lista;
  LIMPA_TELA;
  printf("CONTEUDO DA LISTA");
  if(aux == NULL){
    printf("Lista Vazia!");
  }
  else{
    do{
      printf("\nNome completo: %s", aux->conteudo.nomeCompleto);
      printf("\nTelefone: %s", aux->conteudo.telefone);
      printf("\nEndereço: %s", aux->conteudo.endereco);
      printf("\nCEP: %u", aux->conteudo.cep);
      printf("\nData Nascimento: %s", aux->conteudo.dataNascimento);
      printf("\nFim do registro: %s", aux->conteudo.cifrao);
      printf("\n");
      aux = aux->proximo;
    }while(aux != NULL);
  }
  printf("\nAperte ENTER para sair... ");
  LIMPA_BUFFER;
  getchar();

}

void pesquisaElemento(No *lista){
  //Variaveis
  char nomePesquisado[MAXNOMEENDERECO];
  No *auxLista;

  //Instruções
  LIMPA_TELA;
  printf("Insira o nome completo do registro que deseja buscar: ");
  entradaString(nomePesquisado,MAXNOMEENDERECO);

  for (auxLista = lista; auxLista != NULL; auxLista = auxLista->proximo){
    if (strcmp(auxLista->conteudo.nomeCompleto, nomePesquisado) == 0){
      printf("\nNome completo: %s", auxLista->conteudo.nomeCompleto);
      printf("\nTelefone: %s", auxLista->conteudo.telefone);
      printf("\nEndereço: %s", auxLista->conteudo.endereco);
      printf("\nCEP: %u", auxLista->conteudo.cep);
      printf("\nData Nascimento: %s", auxLista->conteudo.dataNascimento);
      printf("\nFim do registro: %s", auxLista->conteudo.cifrao);
      printf("\n");
    }
  }
  printf("\nAperte ENTER para sair... ");
  LIMPA_BUFFER;
  getchar();
}

No* excluiElemento(No* lista){
  //Variaveis
  No *aux;
  char nomePesquisado[MAXNOMEENDERECO];

  //Instruções
  LIMPA_TELA;
  printf("\nInsira o nome completo do registro que deseja APAGAR: ");
  entradaString(nomePesquisado,MAXNOMEENDERECO);

  aux = lista;
  while(aux != NULL && (strcmp(aux->conteudo.nomeCompleto, nomePesquisado) != 0)){
   aux = aux->proximo;
  }
   if(aux->anterior == NULL){
     lista = aux->proximo;
   }else{
     aux->anterior->proximo = aux->proximo;
   }
   if(aux->proximo != NULL){
     aux->proximo->anterior = aux->anterior;
   }
   free(aux);
   printf("\nCONTATO EXCLUIDO!\n");
   sleep(1);
   return lista;
}

void escreveArquivo(No *lista, FILE *arq){
  //Variaveis
  No *aux;
  //Instruções
  aux = lista;
  do{
    fprintf(arq,"%s",aux->conteudo.nomeCompleto);
    fprintf(arq,"\n");
    fprintf(arq, "%s", aux->conteudo.telefone);
    fprintf(arq,"\n");
    fprintf(arq, "%s", aux->conteudo.endereco);
    fprintf(arq,"\n");
    fprintf(arq, "%u", aux->conteudo.cep);
    fprintf(arq,"\n");
    fprintf(arq, "%s", aux->conteudo.dataNascimento);
    fprintf(arq,"\n");
    fprintf(arq,"%s","$");
    fprintf(arq, "\n");
    aux = aux->proximo;
  }while(aux != NULL);
}

//Do final para o inicio
void liberarLista(No *lista){
  //Variaveis
  No *aux, *aux2;

  //Instruções
  aux = lista;
  if (lista == NULL) {
    printf("Lista Vazia\n");
    return;
  }
  do{
    aux2 = aux;
    aux = aux->proximo;
  }while(aux != NULL);

  do{
    aux = aux2;
    aux2 = aux2->anterior;
    aux->proximo = NULL;
    aux->anterior = NULL;
    printf("Apagando: %s\n", aux->conteudo.nomeCompleto);
    //free(aux->conteudo);
    free(aux);
  }while(aux2 != NULL);

  printf("\nAperte ENTER para sair... ");
  LIMPA_BUFFER;
  getchar();

  lista = NULL;
}
