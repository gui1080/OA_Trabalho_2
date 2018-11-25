/**
 * @file main.c
 *
 * @brief Arquivo com a manipulação das Listas 
 *
 * @author Guilherme Braga e Gabriel Matheus.
 *
 */

//--------------------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include "headers.h"
#include <time.h>
#define max_Chaves = 200;
/*
Feito por:
Gabriel Matheus da Rocha de Oliveira, 17/0103498
Guilherme Braga Pinto, 17/0162290
Last Update: 03/11/2018
UnB- CIC
*/

//--------------------------------------------------------------------------------------------

int main (){

	FILE *fp;
	BTree *tree;
	fp = fopen ("lista.txt", "r");
	int Linha_Index = 1;
	int option;

	int linhas, i, k, num;

	printf("Quantas linhas o arquivo possui?\n");
	scanf("%d", &num);
	//num = num*2;

	int order;

	printf("Digite a ordem da sua B-Tree: ");
	scanf("%d%*c", &order);

	tree = New_tree(order);

	char linha[108];
	char indice_prim[num][8];
	char nome_texto[num][41];
	char matricula_texto[num][7];
	char curso_texto[num][4];
	node_position pos;

	int l = 0;

	for(k=0; k<num ; k++){
	    for(i = 0; i<8; i++){
        	indice_prim[k][i] = ' ';     
    	 }
	}

	for(k = 0; k < num; k++){

		memset(linha, ' ', sizeof(linha));
		fgets(linha, 108, fp);
		linha[108] = '\0';

		for(i = 0; i<108; i++){
			printf("%c", linha[i]);
		}
		printf("\n");
		
		memset(nome_texto, ' ', sizeof(nome_texto));

		for(i=0 ; i<7; i++){
			matricula_texto[k][i] = ' ';
		}

		for(i=0 ; i<4; i++){
			curso_texto[k][i] = ' ';
		}
	
	
		l=0;
	    for(i = 0; i < 41; i++){
	        nome_texto[k][i] = linha[i];
	        if( (linha[i] <= 'Z') && (linha[i] >= 'A') && (l < 3) ) {          
	          indice_prim[k][l] = linha[i];
	          l++;
	        }
		}
		for(i=0 ; i<6; i++){
			matricula_texto[k][i] = linha[i+42];
			indice_prim[k][i+l] = linha[i+42];
		}
		indice_prim[k][7] = '\0';
		pos = Insert_btree(tree, indice_prim[k], Linha_Index);
		Linha_Index++;	
		
	}

//--------------------------------------------------------------------------------------------

	//PRINTANDO OS INDICES PRIMARIOS
	printf("\n");
	
	for(k = 0; k<num; k++){
		for(i=0; i<8; i++){

			printf("%c", indice_prim[k][i]);

		}
		printf("\n");
	}

	char Chave[7];

	printf("\033[1;34m");

	while(1){

  	printf("\n\nO que deseja fazer agora?\n\n");
	
	printf("1 - Pesquisar Registro\n");
  	printf("2 - Adicionar Registro\n");
  	printf("3 - Excluir Registro\n");
  	printf("4 - Salvar e sair do programa\n");

	printf("\033[0m");	
	scanf("%d", &option);

	if(option == 1){

		printf("Digite uma CHAVE para pesquisar: ");
		scanf("%s", Chave);
		Chave[7] = '\0'; 
		pos = btree_find(tree, Chave);
		if (pos.node == NULL) {
			printf("A CHAVE %s não foi encontrada na B-Tree\n", Chave);
		}
		else {
			printf("A CHAVE %s foi encontrada associada a linha '%d'\n",
			         Chave, pos.node->Chaves[pos.index]->linha);
		}

	}
	
	if(option == 2){
		printf("Digite uma CHAVE que será associada a linha %d: ", Linha_Index);
			scanf("%s", Chave);
			Chave[8] = '\0';  
			pos = Insert_btree(tree, Chave, Linha_Index);
			Linha_Index++;		

	}


	if(option == 3){
		printf("Digite uma CHAVE para remover: ");
		scanf("%s", Chave);
		Chave[7] = '\0'; 
		pos = btree_remove(tree, Chave);
		if (pos.node == NULL) {
			printf("A CHAVE %s não foi encontrada na B-Tree\n", Chave);
		}
		else {
			printf("A CHAVE %s foi removida com sucesso\n", Chave);
		}
	}
		
if(option == 4){
	break;
}

}


/*
	for(k = 0; k<num; k++){
		for(i=0; i<41; i++){

			printf("%c", nome_texto[k][i]);

		}
		printf("\n");
	}

	/*
	for(k = 0; k<num; k++){
		for(i=0; i<7; i++){

			printf("%c", matricula_texto[k][i]);

		}
		printf("\n");
	}

	for(k = 0; k<num; k++){
		for(i=0; i<4; i++){

			printf("%c", curso_texto[k][i]);

		}
		printf("\n");
	}
		*/
btree_delete_h(tree);
  return 0;
}


