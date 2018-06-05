//Integrantes
//Gabriela Moraes - 16/0006872
//Guilherme Siqueira - 16/0007763
//Kamilla Costa - 16/0010969

#include "funcoes.h"

int main(int argc, char *argv[]){
  setlocale(LC_ALL, "Portuguese");

  //Declaracoes
  Fila *fAprox = NULL, *fDec = NULL, *fPista1 = NULL, *fPista2 = NULL, *fPista3 = NULL;
  int nVoos = NUMMINVOOS, nAproximacoes = NUMMINAPROXDECOLAGEM, nDecolagens = NUMMINAPROXDECOLAGEM, combA[NUMMAXAPROXDECOLAGEM];
  int vetInformacoes[3];
  Info info;
  char statusDec = 'D', statusAprox = 'A';
  char *codVoos[NUMMAXVOOS] = {"VG3001","JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009", "AZ1008", "AZ1010", "TG1506",
                  "VG3002", "JJ4402", "GL7603", "RL7880", "AL0012","TT4544", "TG1505", "VG3003","JJ4403", "JJ4401",
                  "LN7002", "AZ1002","AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001","LN7003",
                  "AZ1004", "TG1504", "AZ1005", "TG1502", "GL7601","TT4500", "RL7801", "JJ4410", "GL7607", "AL0029",
                  "VV3390", "VV3392","GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065","LF0978",
                  "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510","TT1020", "AZ1098", "BA2312", "VG3030",
                  "BA2304", "KL5609","KL5610", "KL5611"};
  //Instrucoes
  sorteiaNumero(combA, vetInformacoes);
  nVoos = *(vetInformacoes + 0);
  nAproximacoes = *(vetInformacoes + 1);
  nDecolagens = *(vetInformacoes + 2);
  char *codAproximacoes[nAproximacoes], *codDecolagens[nDecolagens];
  selecionaCodigosVoos(vetInformacoes, codVoos, codAproximacoes, codDecolagens);

  //Pistas
  fPista1 = criaFilaPista1();
  fPista2 = criaFilaPista2();
  fPista3 = criaFilaPista3();

  //Aproximação
  fAprox = criaFilaAproximacao();
  for(int i = 0; i < nAproximacoes; i++){
    insereFila(fAprox, codAproximacoes, statusAprox, i, combA);
//    insereFilaPista(fPista1, fAprox);
    //info = desenfileiraFila(fAprox); //pra desenfileirar tudo, sobe isso pra dentro do for
  }

  printf("\n\n\n=============LISTA DE APROXIMAÇÃO =======================");
  imprimeFila(fAprox);
  //Decolagem
  fDec = criaFilaDecolagem();
  for(int i = 0; i < nDecolagens; i++){
    insereFila(fDec, codDecolagens, statusDec, i, combA);
    insereFilaPista(fPista3, fDec);
  }

  printf("\n\n\n============= PISTA 1 =======================");

  No* aux2;
  //for(aux2 = f->inicio; aux2 != NULL; aux2 = aux2->prox){
  //while (fAprox->fim != NULL && fDec->fim != NULL) {
    if (fPista1->inicio == NULL) {
      insereFilaPista(fPista1, fAprox);
      printf("P1\n" );
    }else if(fPista1->inicio != NULL && fPista2->inicio == NULL){
      printf("P2\n" );
      insereFilaPista(fPista2, fAprox);
    }
//  }


  printf("\n\n\n=============LISTA DE DECOLAGENS =======================");
  imprimeFila(fDec);

  printf("\n\n\n=============FILA DA PISTA 1 =======================");
  imprimeFila(fPista1);

  printf("\n\n\n=============LISTA DA PISTA 2 =======================");
  imprimeFila(fPista2);

  printf("\n\n\n=============LISTA DA PISTA 3 =======================");
  imprimeFila(fPista3);

  imprimeResultados(vetInformacoes);


  return 0;
}
