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

void trataFgets(char *string, int tamanho, FILE *arq){
  int penultimo;

  LIMPA_BUFFER;
	fgets(string, tamanho, arq);
	penultimo = strlen(string) - 1;
	if(string[penultimo] == '\n'){
		string[penultimo] = '\0';
	}
}

void leArquivo(FILE *arq, int qtdRegistros){
  //Variaveis
  char fim[100];
  contato *contatosExistentes = NULL;

  //Instruções
  contatosExistentes = (contato *) malloc(qtdRegistros * sizeof(contato));
  if(contatosExistentes == NULL){
    printf("\nAlocação falhou!");
    exit(2);
  }
  fseek(arq, 0, SEEK_SET);
  for(int i = 0; i < qtdRegistros; i++){
    trataFgets(contatosExistentes->nomeCompleto, MAXNOMEENDERECO, arq);
    trataFgets(contatosExistentes->telefone, MAXTELEFONEDATA, arq);
    fgetc(arq);
    trataFgets(contatosExistentes->endereco, MAXNOMEENDERECO, arq);
    fscanf(arq, "%u\n",&contatosExistentes->cep);
    fgetc(arq);
    trataFgets(contatosExistentes->dataNascimento, MAXTELEFONEDATA, arq);
    fgetc(arq);
    trataFgets(contatosExistentes->cifrao,1, arq);
    fgetc(arq);
    printf("\nNome: %s", contatosExistentes->nomeCompleto);
    printf("\nTelefone: %s", contatosExistentes->telefone);
    printf("\nEndereço: %s", contatosExistentes->endereco);
    printf("\nCEP: %u", contatosExistentes->cep);
    printf("\nData de nascimento: %s", contatosExistentes->dataNascimento);
    //printf("\nCifrao: %s", contatosExistentes->cifrao);
    printf("\n");
  }
}

void validaNome(char *nome) {
  //Instruções
  while(strlen(nome) < 3 || strstr(nome, " ") == NULL){
    printf("\nNome inválido.");
		printf("\nNome completo (MAX: %d): ", (MAXNOMEENDERECO - 1));
    LIMPA_BUFFER;
    fgets(nome,MAXNOMEENDERECO,stdin);
  }
}

void validaTelefone(char *telefone){
  //Instruções
  while(telefone[5] != '-' || strlen(telefone) < (MAXTELEFONEDATA - 1)){
    printf("\nFormato inválido.");
    printf("\nTelefone (FORMATO: xxxxx-xxxx): ");
    LIMPA_BUFFER;
    fgets(telefone,MAXTELEFONEDATA,stdin);
  }
}


void validaDataNascimento(char *dataNascimento){
  //Instruções
  while(dataNascimento[2] != '/' || dataNascimento[5] != '/' || strlen(dataNascimento) < (MAXTELEFONEDATA - 1)){
    printf("\nFormato inválido.");
    printf("\nData de nascimento (FORMATO: dd/mm/aaaa): ");
    LIMPA_BUFFER;
    fgets(dataNascimento, MAXTELEFONEDATA, stdin);
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
    LIMPA_BUFFER;
    fgets(novoContato.nomeCompleto, MAXNOMEENDERECO, stdin);
    validaNome(novoContato.nomeCompleto);
    printf("\nTelefone (FORMATO: xxxxx-xxxx): ");
    LIMPA_BUFFER;
    fgets(novoContato.telefone, MAXTELEFONEDATA, stdin);
    validaTelefone(novoContato.telefone);
    printf("\nEndereço (MAX: %d): ", (MAXNOMEENDERECO - 1));
    LIMPA_BUFFER;
    fgets(novoContato.endereco, MAXNOMEENDERECO, stdin);
    printf("\nCEP: ");
   // scanf("%u", &novoContato.cep);
    printf("\nData de nascimento (FORMATO: dd/mm/aaaa): ");
    LIMPA_BUFFER;
    fgets(novoContato.dataNascimento, MAXTELEFONEDATA, stdin);
    validaDataNascimento(novoContato.dataNascimento);
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

    return lista;
}
