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
#include <string.h>

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
	fp = fopen ("lista.txt", "r");

	int linhas, i, k, num;

	printf("Quantas linhas o arquivo possui?\n");
	scanf("%d", &num);
	//num = num*2;

	char linha[108];
	char indice_prim[num][8];
	char nome_texto[num][41];
	char matricula_texto[num][7];
	char curso_texto[num][4];

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

  return 0;
}
