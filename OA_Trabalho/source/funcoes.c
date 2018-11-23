/**
 * @file funcoes.c
 *
 * @brief Arquivo com as funções auxiliares da manipulação das Listas 
 *
 * @author Guilherme Braga e Gabriel Matheus
 *
 */


#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "headers.h"

/*
Feito por:
Guilherme Braga Pinto
Gabriel Matheus da Rocha de Oliveira
Last Update: xx/xx/2018
UnB
*/


void Escreve_Menu(int opt){
	printf("\033[1;34m");
	if(opt == 1){
		printf("\n\n");
  		printf("Lista criada com sucesso!\n");
  		printf("O que deseja fazer agora?\n\n");
	}

	if(opt == 2){
  		printf("1 - Adicionar Registro\n");
  		printf("2 - Excluir Registro\n");
  		printf("3 - Atualizar Registro\n");
  		printf("4 - Salvar e sair do programa\n");
  	}

  	if(opt == 3){
 		printf("Para ler a Lista 1, digite 0\n");
        printf("Para ler a Lista 2, digite 1\n");              // Menus!
        printf("Para intercalar Listas, digite 2\n");
	}
	if(opt == 4){
	  printf("O que deseja modificar?\n");
      printf("1 - Matricula\n");
      printf("2 - Nome\n");
      printf("3 - Opção\n");
      printf("4 - Turma\n");
      printf("5 - Curso\n");
	}
	printf("\033[0m");	
}