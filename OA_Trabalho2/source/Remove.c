#include "headers.h"

node_position btree_remove(BTree* bt, char* Chave) {

  node_position pos = Remove_node_btree(bt->raiz, Chave, bt->order);
  if (bt->raiz->n_Chaves == 0 && pos.node != NULL && pos.node != bt->raiz) {

    bt->raiz = bt->raiz->filhos[0];
  }

  return pos;
}

node_position Remove_node_btree(Nodulo *node, char *Chave, int order) {

  int pos;
  if (Find_node_Chave(node, Chave, &pos)) {

    if (node->Folha) {

      free(node->Chaves[pos]);
      node->n_Chaves--;

      Deslocate_keys_up(node, node, pos, node->n_Chaves, 0, 1);

      return New_node_position(node, pos);
    }
    else {

      Nodulo *left = node->filhos[pos];
      Nodulo *right = node->filhos[pos+1];
      if (left->n_Chaves >= order) {

        free(node->Chaves[pos]);

        node_position max = Find_node_max(left);
        Dados *p = Copy_data(max.node->Chaves[max.index]);

        node->Chaves[pos] = p;

        Remove_node_btree(left, p->Chave, order);
        return New_node_position(node, pos);
      }
      else if (right->n_Chaves >= order) {

        free(node->Chaves[pos]);

// ------------------------------------------- PRESTA ATENÇÃO AQUI -----------------------------------------

        node_position min = Find_node_min(right);
        Dados *p = Copy_data(min.node->Chaves[min.index]);
        node->Chaves[pos] = p;

        Remove_node_btree(right, p->Chave, order);
        return New_node_position(node, pos);
      }
      else {

        left->Chaves[order-1] = node->Chaves[pos];

        Deslocate_keys_up(left, right, 0, order-1, order, 0);
        Deslocate_children_up(left, right, 0, order, order, 0);
        left->n_Chaves = 2*order - 1;

        Delete_node(right);

        Deslocate_keys_up(node, node, pos, node->n_Chaves-1, 0, 1);
        Deslocate_children_up(node, node, pos, node->n_Chaves-1, 1, 2);
        node->n_Chaves--;

        return Remove_node_btree(left, Chave, order);
      }
    }
  }
  else {
    if (node->Folha) {

      return New_node_position(NULL, -1);
    }

    Nodulo *next = node->filhos[pos];

    if (next->n_Chaves == order-1) {
      Nodulo *left = next;

      Nodulo *right;
      if (pos == node->n_Chaves) {
        Nodulo *tmp = left;
        left = node->filhos[pos-1];
        right = tmp;
      }
      else {
        right = node->filhos[pos+1];
      }

      if (left->n_Chaves >= order) {

//---------------------------------- SEGUNDA PARADA -------------------------------------        

        node_position max = Find_node_max(left);
        Dados *p = Copy_data(max.node->Chaves[max.index]);

        Remove_node_btree(left, p->Chave, order);

        Insert_btree_nonfull(right, node->Chaves[pos-1], order);

        node->Chaves[pos-1] = p;

        return Remove_node_btree(right, Chave, order);
      }
      else if (right->n_Chaves >= order) {

        node_position min = Find_node_min(right);
        Dados *p = Copy_data(min.node->Chaves[min.index]);

        Remove_node_btree(right, p->Chave, order);

        Insert_btree_nonfull(left, node->Chaves[pos-1], order);

        node->Chaves[pos-1] = p;

        return Remove_node_btree(left, Chave, order);
      }
      else {

        left->Chaves[order-1] = node->Chaves[pos-1];
        Deslocate_keys_up(node, node, pos, node->n_Chaves-1, 0, 1);
        Deslocate_children_up(node, node, pos+1, node->n_Chaves, 0, 1);
        node->n_Chaves--;

        Deslocate_keys_up(left, right, 0, order-1, order, 0);
        Deslocate_children_up(left, right, 0, right->n_Chaves+1, order-1, 0);
        Delete_node(right);

        left->n_Chaves = 2*order-1;
        return Remove_node_btree(left, Chave, order);
      }
    }

    return Remove_node_btree(next, Chave, order);
  }
}

void btree_delete_s(BTree *bt) {

  while (bt->raiz->n_Chaves > 0) {

    btree_remove(bt, bt->raiz->Chaves[0]->Chave);
  }

  Delete_node(bt->raiz);
}

void btree_delete_h(BTree *bt) {

  btree_delete_s(bt);
  free(bt);
}

node_position Find_node_min(Nodulo *node) {

  if (node->Folha) {
    return New_node_position(node, 0);
  }
  else {
    return Find_node_max(node->filhos[0]);
  }
}

node_position Find_node_max(Nodulo *node) {

  if (node->Folha) {
    return New_node_position(node, node->n_Chaves-1);
  }
  else {
    return Find_node_max(node->filhos[node->n_Chaves]);
  }
}

Dados* Copy_data(Dados *p) {
  Dados *new = New_data(p->Chave, p->pessoas);
  return new;
}

void Delete_node(Nodulo *node) {
  free(node->filhos);
  free(node->Chaves);
  free(node);
}