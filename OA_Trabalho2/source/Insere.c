#include "headers.h"

/*
Feito por:
Gabriel Matheus da Rocha de Oliveira, 17/0103498
Guilherme Braga Pinto, 17/0162290
Last Update: 08/12/2018
UnB- CIC
*/


// ------------------------------------------------------------------------------------

node_posicao Insert_arvoreb(BTree* bt, char *Chave, struct Aluno pessoas) {

Nodulo *raiz = bt->raiz;

Dados *pair = New_data(Chave, pessoas);                 // insere em arvore

if (raiz->n_Chaves == 2*bt->order -1) {

  Nodulo *new_raiz = New_node(bt->order, false);
  new_raiz->filhos[0] = raiz;

  Split_arvoreb(new_raiz, 0, bt->order);      // split e insere nova raiz
  bt->raiz = new_raiz;

  return Insert_arvoreb_nonfull(new_raiz, pair, bt->order); 
}
else {

  return Insert_arvoreb_nonfull(raiz, pair, bt->order);
  }
}

// ------------------------------------------------------------------------------------

Dados* New_data(char* Chave, struct Aluno pessoas) {
  Dados *p = malloc(sizeof(Dados));

  strcpy(p->Chave, Chave);
  p->Chave[8] = '\0';
  //printf("Chave adicionada eh: %s\n", p->Chave);
  strcpy(p->pessoas.nome, pessoas.nome);
  strcpy(p->pessoas.matricula, pessoas.matricula);
  strcpy(p->pessoas.Curso, pessoas.Curso);                 //atribuimos nova data
  strcpy(p->pessoas.Turma, pessoas.Turma);

  return p;
}

// ------------------------------------------------------------------------------------

void Split_arvoreb(Nodulo *node, int pos, int order) {

Nodulo *y = node->filhos[pos];

Nodulo *z = New_node(order, y->Folha);
z->n_Chaves = order-1;                   // divide a arvore para procura

Deslocate_keys_up(z, y, 0, order-1, 0, order);

  if (!y->Folha) {
    Deslocate_filho_up(z, y, 0, order, 0, order);
  }
  y->n_Chaves = order-1;

  Deslocate_filho_down(node, node, node->n_Chaves, pos, 1, 0);

  node->filhos[pos+1] = z;

  Deslocate_keys_down(node, node, node->n_Chaves-1, pos-1, 1, 0);

  node->Chaves[pos] = y->Chaves[order-1];

  node->n_Chaves++;
}

// ------------------------------------------------------------------------------------

void Deslocate_keys_up(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from) {

  int j;
  for (j = beg; j < end; j++) {   //desloca key pra cima
    to->Chaves[j + padding_to] = from->Chaves[j + padding_from];
  }

}

// ------------------------------------------------------------------------------------

void Deslocate_filho_up(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from) {

  int j;
  for (j = beg; j < end; j++) {    //desloca filho pra cima
    to->filhos[j + padding_to] = from->filhos[j + padding_from];
  }
}

// ------------------------------------------------------------------------------------

void Deslocate_filho_down(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from) {

  int j;
  for (j = beg; j > end; j--) {   //desloca filho pra baixo
    to->filhos[j + padding_to] = from->filhos[j + padding_from];
  }

}

// ------------------------------------------------------------------------------------

void Deslocate_keys_down(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from) {

  int j;
  for (j = beg; j > end; j--) {   //desloca key pra baixo
    to->Chaves[j + padding_to] = from->Chaves[j + padding_from];
  }

}

// ------------------------------------------------------------------------------------

node_posicao Insert_arvoreb_nonfull(Nodulo * node, Dados *pair, int order) {

  int pos = node->n_Chaves - 1;
  if (node->Folha) {

    while (pos >= 0 && compara_string(pair->Chave, node->Chaves[pos]->Chave) == 2) {
      node->Chaves[pos+1] = node->Chaves[pos];
      pos--;
    }

      if(pos >= 0 && compara_string(pair->Chave, node->Chaves[pos]->Chave) == 0){

      pos++;
      while (pos != node->n_Chaves) {
        node->Chaves[pos] = node->Chaves[pos+1];
        pos++;
      }

      return New_node_posicao(NULL, -1);
    }
    else {                       // acha a posição, se necessario cria uma
      pos++;

      node->Chaves[pos] = pair;
      node->n_Chaves++;
      return New_node_posicao(node, pos);
    }
  }
  else {
    while (pos >= 0 && compara_string(pair->Chave, node->Chaves[pos]->Chave) == 2) {
      pos--;
    }
      if(pos >= 0 && compara_string(pair->Chave, node->Chaves[pos]->Chave) == 0){

      return New_node_posicao(NULL, -1);
    }
    else {
      pos++;

      if (node->filhos[pos]->n_Chaves == 2*order-1) {
        Split_arvoreb(node, pos, order);
        if (pair->Chave > node->Chaves[pos]->Chave) {
          pos++;
        }
      }

      return Insert_arvoreb_nonfull(node->filhos[pos], pair, order);
    }
  }
}

// ------------------------------------------------------------------------------------