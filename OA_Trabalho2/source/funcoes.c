#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "headers.h"

/*
Feito por:
Guilherme Braga Pinto
Gabriel Matheus da Rocha de Oliveira
Last Update: 08/12/2018
UnB
*/


void Escreve_Menu(int opt){
	printf("\033[1;34m");
	if(opt == 1){

    printf("Quantas linhas o arquivo possui?\n");
	}

	if(opt == 2){
      printf("Digite a ordem da sua B-Tree: ");
  	}

  	if(opt == 3){
    printf("\n\nO que deseja fazer agora?\n\n");
  
    printf("1 - Pesquisar Registro\n");
    printf("2 - Adicionar Registro\n");
    printf("3 - Excluir Registro\n");
    printf("4 - Salvar e sair do programa\n");
	}
	if(opt == 4){
      printf("Digite uma CHAVE para pesquisar: ");
	}
  if(opt == 5){
      printf("Digite uma CHAVE que será associada as informações\n");
  }
  if(opt == 6){
    printf("Por favor, digite os seguintes dados:\n");
  }
  if(opt == 7){
    printf("Digite uma CHAVE para remover: ");
  }
	printf("\033[0m");	
}

// ------------------------------------------------------------------------------------

BTree* New_tree(int order) {
  BTree* bt = malloc(sizeof(BTree));

  bt->order = order;                     //cria arvore
  bt->raiz = New_node(order, true);

  return bt;
}

// ------------------------------------------------------------------------------------

Nodulo* New_node(int order, bool Folha) {
  Nodulo *n = malloc(sizeof(Nodulo));

  n->n_Chaves = 0;
  n->Folha = Folha;
  n->Chaves = malloc((2*order-1) * sizeof(Dados));
  n->filhos = malloc((2*order) * sizeof(Nodulo*));     //da malloc nos filhos da nova arvore

  return n;
}

// ------------------------------------------------------------------------------------

node_posicao New_node_posicao(Nodulo *node, int index) {
  node_posicao node_pos = {.node = node, .index = index};     //novo filho em posiçao
  return node_pos;
}

// ------------------------------------------------------------------------------------

bool Find_node_Chave(Nodulo *node, char* Chave, int *pos) {
  *pos = 0;

  while ((*pos) < node->n_Chaves && compara_string(Chave, node->Chaves[(*pos)]->Chave) == 1) {
    (*pos)++;        // itera pela arvore incrementando pos, para achar o no
  }

  return (*pos) < node->n_Chaves && compara_string(Chave, node->Chaves[(*pos)]->Chave) == 0;

}

// ------------------------------------------------------------------------------------

node_posicao arvoreb_find(BTree* bt,char* Chave){

  return Find_node_arvoreb(bt->raiz, Chave);      //chamada de funcao
}

// ------------------------------------------------------------------------------------

node_posicao Find_node_arvoreb(Nodulo* node, char *Chave){

  int pos;
  if (Find_node_Chave(node, Chave, &pos)) {
    return New_node_posicao(node, pos);
  }
  else {
    if (node->Folha) {
      return New_node_posicao(NULL, -1);    //define se ha o que se procura, se retorna o que foi pedido se possivel
    }
    else {
      return Find_node_arvoreb(node->filhos[pos], Chave);
    }
  }
}

// ------------------------------------------------------------------------------------

int compara_string(char *string1, char* string2){
int result;

//printf("string 1: %s\nstring 2: %s\n\n", string1, string2);
if (strcmp(string1, string2) == 0){
  return 0;                   //~inválido caso as duas strings sejam iguais
}

for(int i = 0; i < 8; i++){

  if(string1[i] > string2[i]){                  // comparamos  as strings por posição, se são diferentes a função para
    result = 1;    
    //printf("string 1 é maior\n\n");                      // para cada caso, há um retorno diferente 
    break;
    //return 1;
  }if(string1[i] < string2[i]){
    result = 2;
     //printf("string 2 é maior\n\n");  
    break;
    //return 2;
  }
  
}

return result;
}

// ------------------------------------------------------------------------------------