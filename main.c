#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct No {
  int vertice; //número do bloco
  struct No* prox;// ponteiro para o prox no
} No; // struct no

typedef struct Grafo{
  int numVertices; // número do vertice
  No** listaAdj; // matriz de lista adjacente
} Grafo;// sctruct grafo

No* criarNo(int v){
  No* newNo = malloc(sizeof(No)); // alocação do No
  newNo->vertice = v; // define o número do vertice
  newNo->prox = NULL; // aponta o prox para NULL
  return newNo;
}

//Grafo com um vértice
Grafo* criarGrafo(){
  Grafo* grafo = malloc(sizeof(Grafo)); // alocação do Grafo
  grafo->numVertices = 1; // define o numero do bloco
  grafo->listaAdj = malloc(sizeof(No*)); // aloca uma matriz de lista dentro do grafo
  grafo->listaAdj[0] = NULL; // define a posição [0] da matriz para NULL
  
  return grafo;
}

int AcharValor(char linha[]){ // função para achar o label
  char* ini = strrchr(linha,'L'); //procura a última ocorrência do caractere 'L'
  char* valor = strdup(ini+1); // acha o valor copiando a posição ini+1
  return atoi(valor); // retorna o valor convertido de char para int
}

//Vértices 0-indexados
void addLig(Grafo* grafo, int v1, int v2) {// faz a ligação dos blocos no grafo
  if(v2 >= grafo->numVertices) {
    int antigo = grafo->numVertices;
    grafo->numVertices = v2 + 1;
    grafo->listaAdj = realloc(grafo->listaAdj, grafo->numVertices * sizeof(No*)); // realoca o tamanho do grafo de acordo com a quatidade de blocos

    while(antigo < grafo->numVertices) { // limpa o primeiro grafo criado
      grafo->listaAdj[antigo] = NULL;
      antigo++;
    }
  }
  No* newNo = criarNo(v2); // cria um novo No para grafo seguinte
  No* noAtual = grafo->listaAdj[v1]; // define o Noatual
  //Primeiro elemento (da lista ou por ordenação)
  if(noAtual == NULL || newNo->vertice < noAtual->vertice) {
    newNo->prox = noAtual;
    grafo->listaAdj[v1] = newNo;
    return;
  }

  //Elementos posteriores
  while(noAtual->prox != NULL && noAtual->prox->vertice < newNo->vertice) {
    newNo = noAtual->prox;
  }

  newNo->prox = noAtual->prox;
  noAtual->prox = newNo;

}

void imprimir(Grafo* grafo){
  int v;
  printf("\nControl Flow Graph:\n");
  printf("\nEntry --> B1");// define a entrada
  for(v = 0; v < grafo->numVertices; v++){
    No* temporario = grafo->listaAdj[v]; // cria um no temporario para impressão
    printf("\nB%d --> ", v+1);

    while(temporario){
      printf("%d ",temporario->vertice+1);
      temporario = temporario->prox;
    }
  }
  printf("Exit");// define a saída
  printf("\n");
}

int readArq(Grafo *grafo){
  int sg = 0; // inteiro que representa o número de goto presentes na entrada
  int savegoto[100], refgoto[100],salval[100]; // array's que definem qual bloco se liga a qual label presente em outro bloco
  int numblock = grafo->numVertices; // define o número de blocos
  int numlinhas=0, i = 0;
  char instructions[100]; 
  char *codigo[100];
  FILE *arquivo;// abre o arquivo
  arquivo = fopen("arq1.txt", "r");
  if(arquivo == NULL){// se o arquivo não existir retorna uma mensagem de erro
    printf("\nFalha ao abrir arquivo\n");
    return 0;
  }

  while(fgets(instructions, sizeof instructions, arquivo)!= NULL){
    codigo[i] = strdup(instructions);// copia as intruções presentes no arquivo
    i++;
    numlinhas++;
  }
  printf("\nInstructios:\n\n");
  for (int j = 0; j < numlinhas; j++){
    printf("%s", codigo[j]); // imprime as instruções gravada no vetor
  }
  char word1[]="if", word2[]="goto", word3[] = "L";// palavras a serem encontradas que definem a criação de um novo bloco no gráfico
  printf("\n\nBlocos:\n");
  printf("\nB%i:  ", numblock);
  for(int i = 0; i < numlinhas; i++){
    printf("%s",codigo[i]);
    if((strstr(codigo[i],word1)) && (i < numlinhas-1)){// comparação cara criação dos blocos
      addLig(grafo,(numblock)-1,(numblock));

      savegoto[sg] = numblock; //coloca no array que o bloco tem um goto
      refgoto[sg] = AcharValor(codigo[i]); // acha a qual label esse bloco deseja se ligar
      sg++;// incrementa o total de goto salvos
      numblock++; // incrementa a quantidade de blocos

      printf("\nB%i:  ", numblock);
    }else { 
      if (strstr(codigo[i],word2) && (i < numlinhas-1)){
        savegoto[sg] = numblock; //coloca no array que o bloco tem um goto
        refgoto[sg] = AcharValor(codigo[i]); // acha a qual label esse bloco deseja se ligar
        sg++; // incrementa o total de goto salvos
      }
      
      if (i <= numlinhas -2 && codigo[i+1][0] == word3[0]){// comparação cara criação dos blocos
        if(codigo[i][0] != 'g' && codigo[i][1] != 'o' && codigo[i][2] != 't' && codigo[i][3] != 'o'){
        addLig(grafo,(numblock)-1,numblock);
        }
        numblock++; // incrementa a quantidade de blocos
        printf("\nB%i:  ", numblock);
      }

      if (i <= numlinhas -2 && codigo[i+1][0] == word3[0]){
      salval[codigo[i+1][1]-'0'] = numblock;// salva que esse bloco é um label
      }
    }
  }

  for(int i = 0; i < sg; i++){ // faz as ligações dos blocos que possuem goto
    addLig(grafo,savegoto[i]-1,salval[refgoto[i]]-1);
  }

  printf("\n\n");
  fclose(arquivo);// fecha o arquivo
  return 1;
}

int main(){
  struct Grafo* grafo = criarGrafo(); // cria o primeiro grafo
  if(readArq(grafo)){; // lê o arquivo
  imprimir(grafo);// imprime o grafo
  }
  printf("\n\n");
  return 0;
}