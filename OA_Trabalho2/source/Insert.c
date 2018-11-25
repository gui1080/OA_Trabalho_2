#include "headers.h"

node_position Insert_btree(BTree* bt, char *Chave, int linha) {

Nodulo *raiz = bt->raiz;

Dados *pair = New_data(Chave, linha);

if (raiz->n_Chaves == 2*bt->order -1) {

Nodulo *new_raiz = New_node(bt->order, false);
new_raiz->filhos[0] = raiz;

Split_btree(new_raiz, 0, bt->order);
bt->raiz = new_raiz;

    return Insert_btree_nonfull(new_raiz, pair, bt->order);
  }
  else {

    return Insert_btree_nonfull(raiz, pair, bt->order);
  }
}

Dados* New_data(char* Chave, int linha) {
  Dados *p = malloc(sizeof(Dados));

  strcpy(p->Chave, Chave);
  p->linha = linha;

  return p;
}

void Split_btree(Nodulo *node, int pos, int order) {

Nodulo *y = node->filhos[pos];

Nodulo *z = New_node(order, y->Folha);
z->n_Chaves = order-1;

Deslocate_keys_up(z, y, 0, order-1, 0, order);

  if (!y->Folha) {
    Deslocate_children_up(z, y, 0, order, 0, order);
  }
  y->n_Chaves = order-1;

  Deslocate_children_down(node, node, node->n_Chaves, pos, 1, 0);

  node->filhos[pos+1] = z;

  Deslocate_keys_down(node, node, node->n_Chaves-1, pos-1, 1, 0);

  node->Chaves[pos] = y->Chaves[order-1];

  node->n_Chaves++;
}

void Deslocate_keys_up(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from) {

  int j;
  for (j = beg; j < end; j++) {
    to->Chaves[j + padding_to] = from->Chaves[j + padding_from];
  }

}

void Deslocate_children_up(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from) {

  int j;
  for (j = beg; j < end; j++) {
    to->filhos[j + padding_to] = from->filhos[j + padding_from];
  }
}

void Deslocate_children_down(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from) {

  int j;
  for (j = beg; j > end; j--) {
    to->filhos[j + padding_to] = from->filhos[j + padding_from];
  }

}

void Deslocate_keys_down(Nodulo *to, Nodulo *from, int beg, int end, int padding_to, int padding_from) {

  int j;
  for (j = beg; j > end; j--) {
    to->Chaves[j + padding_to] = from->Chaves[j + padding_from];
  }

}

node_position Insert_btree_nonfull(Nodulo * node, Dados *pair, int order) {

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

      return New_node_position(NULL, -1);
    }
    else {
      pos++;

      node->Chaves[pos] = pair;
      node->n_Chaves++;
      return New_node_position(node, pos);
    }
  }
  else {
    while (pos >= 0 && compara_string(pair->Chave, node->Chaves[pos]->Chave) == 2) {
      pos--;
    }
      if(pos >= 0 && compara_string(pair->Chave, node->Chaves[pos]->Chave) == 0){

      return New_node_position(NULL, -1);
    }
    else {
      pos++;

      if (node->filhos[pos]->n_Chaves == 2*order-1) {
        Split_btree(node, pos, order);
        if (pair->Chave > node->Chaves[pos]->Chave) {
          pos++;
        }
      }

      return Insert_btree_nonfull(node->filhos[pos], pair, order);
    }
  }
}