/**
 * @file headers.h
 *
 * @brief Arquivo com as declarações das funções auxiliares da manipulação das Listas 
 *
 * @author Guilherme Braga e Gabriel Matheus
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*
Feito por:
Gabriel Matheus da Rocha de Oliveira, 17/0103498
Guilherme Braga Pinto, 17/0162290
Last Update: 03/11/2018
UnB- CIC
*/

//--------------------------------------------------------------------------------------------

/**
 * @brief Mostra menus, um atalho de prints.
 * 
 * @param int opt - Descreve qual menu se mostrará.
 */

struct Aluno
{
	char nome[30];
	char matricula[5];
    char Curso[2];
    char Turma;
};

typedef struct Dados {
	char Chave[8];
	struct Aluno pessoas;
} Dados;

typedef struct Nodulo {
	bool Folha;
	int n_Chaves;

	struct Nodulo **filhos;
	Dados **Chaves;
} Nodulo;

typedef struct node_position_t {
	Nodulo *node;
	int index;
} node_position;

typedef struct Arvore_B {
	int order;
	Nodulo *raiz;
} BTree;


BTree* New_tree(int order);

Nodulo* New_node(int order, bool Folha);

node_position Insert_btree(BTree* bt, char *Chave, struct Aluno pessoas);

Dados* New_data(char *Chave, struct Aluno pessoas); 

void Split_btree(Nodulo *node, int pos, int order); 

void Deslocate_keys_up(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from);

void Deslocate_keys_down(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from);

void Deslocate_children_up(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from);

void Deslocate_children_down(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from);

node_position Insert_btree_nonfull(Nodulo * node, Dados *pair, int order);

node_position New_node_position(Nodulo *node, int index);

bool Find_node_Chave(Nodulo *node, char* Chave, int *pos);

node_position btree_find(BTree* bt,char* Chave);

node_position Find_node_btree(Nodulo* node, char *Chave);

int compara_string(char *string1, char* string2);

node_position btree_remove(BTree* bt, char* Chave);

node_position Remove_node_btree(Nodulo *node, char *Chave, int order);

node_position Find_node_min(Nodulo *node); 

node_position Find_node_max(Nodulo *node);

Dados* Copy_data(Dados *p);

void Escreve_Menu(int opt);

void btree_delete_s(BTree *bt);

void btree_delete_h(BTree *bt);

void Delete_node(Nodulo *node);