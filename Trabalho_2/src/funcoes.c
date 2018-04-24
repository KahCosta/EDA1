#include "funcoes.h"
#include <string.h>

int sorteiaNumero(int *treinamentoGrass){
  int numSorteado, vetor[NUMMAX] = {51}, situacao;
  FILE *arq;

  srand((unsigned) time(NULL));
  printf("Conjunto de Treinamento: \n");
  for(int i = 0; i < NUMMAX; i++){
    do{
      numSorteado = ((rand() % FILEMAX) + 1);
      situacao = NREPETIDO;
      for(int aux = 0; aux < NUMMAX; aux++){
        if(numSorteado == vetor[aux]){
            situacao = REPETIDO;
        }
      }
    }while(situacao == REPETIDO);
    vetor[i] = numSorteado;
    treinamentoGrass[i] = vetor[i];
    printf("%d ", treinamentoGrass[i]);
    abreArquivo(arq, numSorteado);
  }
  printf("\n\n");
}

int comparaVetor(int *treinamentoGrass, int *testeGrass){
  int vetorCompara[FILEMAX] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
                              26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50};
  int j=0;
  int comparador = 0;
  int vet[NUMMAX];
  int soma = 0;
  FILE *arq;
  for(int i = 0; i < FILEMAX; i++){
      soma=0;
      comparador = vetorCompara[i];//pega um valor e do vetor de 50 posições e vê se ele existe em treinamentoGrass
    for(int aux = 0; aux < NUMMAX; aux++){
      if(comparador != *(treinamentoGrass + aux)){
        soma++; //Só vê se o valor não existe em treinamentoGrass
      }else{
        vet[aux] = comparador; //se já existe no vetor de treinamento ele guarda num vetor qualquer
        break;
      }
    }
      if(soma == 25 ){ //se entrou nesse if é porque percorreu todo o vetor de treinamento e não encontrou nenhum
                        //valor igual ao do vetor compara
        testeGrass[j] = comparador; //usa j porque se não, na vez que o comparador existir em treinamentoGrass,

        j++;
          if(j==25) //Como o for mais externo vai até 50 e testeGrass tem tamanho 25, tem que testar j<25
            break;
      }
  }
  printf("Conjunto de Teste: \n");
  for (int j=0; j<NUMMAX; j++) {
    printf("%d ", testeGrass[j]);
    abreArquivo(arq, comparador);
  }
  puts("");
}

void abreArquivo(FILE *arq, int num){
  int i;
  char arquivo[29]; //29 é o numero de caracteres do caminho d arq de grama
  if(num < 10)
    snprintf(arquivo, sizeof(arquivo), "%s0%d%s", "./DataSet/grass/grass_", num, EXTENSION);
  else
    snprintf(arquivo, sizeof(arquivo), "%s%d%s", "./DataSet/grass/grass_", num, EXTENSION);

   if((arq=fopen(arquivo,"rt"))==NULL){
       puts("Não foi encontrado registro ");
       getchar();
    }
    leArquivo(arq);
    fechaArquivo(arq);
}

void leArquivo(FILE *arq){
  char detectorPonto;
  int contLinha = 0, contColuna = 0;
  fseek(arq, 0, SEEK_SET);

  while(fread(&detectorPonto,sizeof(char),1,arq)==1){
    if(detectorPonto == '\n'){
      contLinha++;
      contColuna++;
    }
    if(detectorPonto == ';'){
      contColuna++;
    }
  }
  contColuna/=contLinha; //divisão
  printf("%d ", contLinha);
  printf("%d\n", contColuna);
}
void fechaArquivo(FILE *arq){
  fclose(arq);
}
