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
    arq = fopen(nomeArquivo, "w+");
  }
  return arq;
}

void darBoasVindas(){
  LIMPA_TELA;
  printf("Seja bem vindo a Agenda Pessoal");
  printf("\nEstamos carregando seus contatos... Por favor, aguarde =)\n");
  for(int i = 0; i < 10; i++){
    sleep(1);
    printf(".\n");
    //__fpurge(stdout);
  }
}

int menu(){
  //Variaveis
  int opcao;

  //Instruções
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
  int penultimo;

  LIMPA_BUFFER;
	fgets(string, tamanho, stdin);
  penultimo = strlen(string) - 1;
	if(string[penultimo] == '\n'){
		string[penultimo] = '\0';
	}
}


void leLinha(char *string, int tamanho, FILE *arq){
  int penultimo;

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

    printf("\nNome: %s", contatosExistentes[registro].nomeCompleto);
    printf("\nTelefone: %s", contatosExistentes[registro].telefone);
    printf("\nEndereço: %s", contatosExistentes[registro].endereco);
    printf("\nCep: %u", contatosExistentes[registro].cep);
    printf("\nData Nascimento: %s", contatosExistentes[registro].dataNascimento);
    printf("\nCifrão: %s\n", contatosExistentes[registro].cifrao);

    lista = insereInicioLista(lista, contatosExistentes[registro]);
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
  //Instruções
  while(telefone[5] != '-' || strlen(telefone) < 10){//(MAXTELEFONEDATA - 1)){
    printf("\nFormato inválido.");
    printf("\nTelefone (FORMATO: xxxxx-xxxx): ");
    entradaString(telefone, MAXTELEFONEDATA);
  }
}


void validaDataNascimento(char *dataNascimento){
  //Instruções
  while(dataNascimento[2] != '/' || dataNascimento[5] != '/' || strlen(dataNascimento) < 10){//(MAXTELEFONEDATA - 1)){
    printf("\nFormato inválido.");
    printf("\nData de nascimento (FORMATO: dd/mm/aaaa): ");
    entradaString(dataNascimento, MAXTELEFONEDATA);
  }
}

void validaOpcao(char opcao){
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

No* insereInicioLista(No* lista, contato novoContato){
    //Variaveis
    No *novoElemento;

    //Instruções

    //fseek(arq, 0, SEEK_SET);

    novoElemento = (No*) malloc(sizeof(No));
    if(novoElemento == NULL){
      printf("\nAlocação falhou!");
      exit(2);
    }

    novoElemento->anterior = NULL;
    novoElemento->conteudo = novoContato;
    if(lista == NULL){
        novoElemento->proximo = NULL;
    }
    else{
      novoElemento->proximo = lista;
      lista->anterior = novoElemento;//Duvida?
    }

    return novoElemento;
}

void imprimeListaFinalproInicio(No *lista){
  No *aux, *aux2;
  aux = lista;
  do{
    aux2 = aux;
    aux = aux->proximo;
  }while(aux != NULL);

  printf("\nCONTEUDO DA LISTA");
  do{
    printf("\nNome completo: %s", aux2->conteudo.nomeCompleto);
    printf("\nTelefone: %s", aux2->conteudo.telefone);
    printf("\nEndereço: %s", aux2->conteudo.endereco);
    printf("\nCEP: %u", aux2->conteudo.cep);
    printf("\nData Nascimento: %s", aux2->conteudo.dataNascimento);
    printf("\nFim do registro: %s", aux2->conteudo.cifrao);
    printf("\n");
    //printf("\nConteudo: %d\n", aux2->conteudo);
    aux2 = aux2->anterior;
  }while(aux2 != NULL);
}

void pesquisaElemento(No *lista){
  char nomePesquisado[MAXNOMEENDERECO];
  No *auxLista;

  printf("\nInsira o nome completo do registro que deseja buscar: ");
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
}

No* excluiElemento(No* lista){
  No *aux;
  char nomePesquisado[MAXNOMEENDERECO];

  aux = (No*) malloc(sizeof(No));

  if(aux == NULL){
    printf("\nAlocação falhou!");
    exit(2);
  }

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
/*
void escreveArquivo(){

      fprintf(arq,"%s",novoElemento->conteudo.nomeCompleto);
      fprintf(arq,"\n");
      fprintf(arq, "%s", novoElemento->conteudo.telefone);
      fprintf(arq,"\n");
      fprintf(arq, "%s", novoElemento->conteudo.endereco);
      fprintf(arq,"\n");
      fprintf(arq, "%u",novoElemento->conteudo.cep);
      fprintf(arq,"\n");
      fprintf(arq, "%s", novoElemento->conteudo.dataNascimento);
      fprintf(arq,"\n");
      fprintf(arq,"%s","$");
      fprintf(arq, "\n");
}
*/
