#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*
Feito por:
Gabriel Matheus da Rocha de Oliveira, 17/0103498
Guilherme Braga Pinto, 17/0162290
Last Update: 08/12/2018
UnB- CIC
*/

//--------------------------------------------------------------------------------------------


struct Aluno
{
	char nome[30];
	char matricula[6];
    char Curso[3];
    char Turma[2];
};

typedef struct Dados {
	char Chave[9];
	struct Aluno pessoas;
} Dados;

typedef struct Nodulo {
	bool Folha;
	int n_Chaves;

	struct Nodulo **filhos;
	Dados **Chaves;
} Nodulo;

typedef struct node_posicao_t {
	Nodulo *node;
	int index;
} node_posicao;

typedef struct Arvore_B {
	int order;
	Nodulo *raiz;
} BTree;

//--------------------------------------------------------------------------------------------

BTree* New_tree(int order);

Nodulo* New_node(int order, bool Folha);

node_posicao Insert_arvoreb(BTree* bt, char *Chave, struct Aluno pessoas);

Dados* New_data(char *Chave, struct Aluno pessoas); 

void Split_arvoreb(Nodulo *node, int pos, int order); 

void Deslocate_keys_up(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from);

void Deslocate_keys_down(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from);

void Deslocate_filho_up(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from);

void Deslocate_filho_down(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from);

node_posicao Insert_arvoreb_nonfull(Nodulo * node, Dados *pair, int order);

node_posicao New_node_posicao(Nodulo *node, int index);

bool Find_node_Chave(Nodulo *node, char* Chave, int *pos);

node_posicao arvoreb_find(BTree* bt,char* Chave);

node_posicao Find_node_arvoreb(Nodulo* node, char *Chave);

int compara_string(char *string1, char* string2);

node_posicao arvoreb_remove(BTree* bt, char* Chave);

node_posicao Remove_no_arvoreb(Nodulo *node, char *Chave, int order);

node_posicao Find_node_min(Nodulo *node); 

node_posicao Find_node_max(Nodulo *node);

Dados* Copy_data(Dados *p);

void Escreve_Menu(int opt);

void arvoreb_delete_s(BTree *bt);

void arvoreb_delete_h(BTree *bt);

void Delete_node(Nodulo *node);