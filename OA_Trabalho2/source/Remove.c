#include "headers.h"


/*
Feito por:
Gabriel Matheus da Rocha de Oliveira, 17/0103498
Guilherme Braga Pinto, 17/0162290
Last Update: 08/12/2018
UnB- CIC
*/


node_posicao arvoreb_remove(BTree* bt, char* Chave) {

  node_posicao pos = Remove_no_arvoreb(bt->raiz, Chave, bt->order);
  if (bt->raiz->n_Chaves == 0 && pos.node != NULL && pos.node != bt->raiz) {

    bt->raiz = bt->raiz->filhos[0];         // damos 0 filhos para raiz
  }

  return pos;
}

node_posicao Remove_no_arvoreb(Nodulo *node, char *Chave, int order) {
 
  int pos;
  if (Find_node_Chave(node, Chave, &pos)) {

    if (node->Folha) {             //achamos o no e removemos

      free(node->Chaves[pos]);
      node->n_Chaves--;          // desloca chave e abaixa o contador 

      Deslocate_keys_up(node, node, pos, node->n_Chaves, 0, 1);

      return New_node_posicao(node, pos);
    }
    else {

      Nodulo *left = node->filhos[pos];
      Nodulo *right = node->filhos[pos+1];        // define novos filhos e repete procedimento para cada caso
      if (left->n_Chaves >= order) {

        free(node->Chaves[pos]);

        node_posicao max = Find_node_max(left);
        Dados *p = Copy_data(max.node->Chaves[max.index]);

        node->Chaves[pos] = p;

        Remove_no_arvoreb(left, p->Chave, order);
        return New_node_posicao(node, pos);
      }
      else if (right->n_Chaves >= order) {

        free(node->Chaves[pos]);


        node_posicao min = Find_node_min(right);
        Dados *p = Copy_data(min.node->Chaves[min.index]);
        node->Chaves[pos] = p;

        Remove_no_arvoreb(right, p->Chave, order);
        return New_node_posicao(node, pos);
      }
      else {

        left->Chaves[order-1] = node->Chaves[pos];

        Deslocate_keys_up(left, right, 0, order-1, order, 0);
        Deslocate_filho_up(left, right, 0, order, order, 0);
        left->n_Chaves = 2*order - 1;

        Delete_node(right);

        Deslocate_keys_up(node, node, pos, node->n_Chaves-1, 0, 1);
        Deslocate_filho_up(node, node, pos, node->n_Chaves-1, 1, 2);
        node->n_Chaves--;

        return Remove_no_arvoreb(left, Chave, order);
      }
    }
  }
  else {
    if (node->Folha) {

      return New_node_posicao(NULL, -1);
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

        node_posicao max = Find_node_max(left);
        Dados *p = Copy_data(max.node->Chaves[max.index]);

        Remove_no_arvoreb(left, p->Chave, order);

        Insert_arvoreb_nonfull(right, node->Chaves[pos-1], order);

        node->Chaves[pos-1] = p;

        return Remove_no_arvoreb(right, Chave, order);
      }
      else if (right->n_Chaves >= order) {

        node_posicao min = Find_node_min(right);
        Dados *p = Copy_data(min.node->Chaves[min.index]);

        Remove_no_arvoreb(right, p->Chave, order);

        Insert_arvoreb_nonfull(left, node->Chaves[pos-1], order);

        node->Chaves[pos-1] = p;

        return Remove_no_arvoreb(left, Chave, order);
      }
      else {

        left->Chaves[order-1] = node->Chaves[pos-1];
        Deslocate_keys_up(node, node, pos, node->n_Chaves-1, 0, 1);
        Deslocate_filho_up(node, node, pos+1, node->n_Chaves, 0, 1);
        node->n_Chaves--;

        Deslocate_keys_up(left, right, 0, order-1, order, 0);
        Deslocate_filho_up(left, right, 0, right->n_Chaves+1, order-1, 0);
        Delete_node(right);

        left->n_Chaves = 2*order-1;
        return Remove_no_arvoreb(left, Chave, order);
      }
    }

    return Remove_no_arvoreb(next, Chave, order);
  }
}

// ------------------------------------------------------------------------------------

void arvoreb_delete_s(BTree *bt) {

  while (bt->raiz->n_Chaves > 0) {

    arvoreb_remove(bt, bt->raiz->Chaves[0]->Chave);        //chamada para deletar em cada no
  }

  Delete_node(bt->raiz);
}

// ------------------------------------------------------------------------------------

void arvoreb_delete_h(BTree *bt) {

  arvoreb_delete_s(bt);   //chamada
  free(bt);
}

// ------------------------------------------------------------------------------------

node_posicao Find_node_min(Nodulo *node) {

  if (node->Folha) {
    return New_node_posicao(node, 0);
  }
  else {
    return Find_node_max(node->filhos[0]);              //chama no minimo ou maximo
  }
}

// ------------------------------------------------------------------------------------

node_posicao Find_node_max(Nodulo *node) {

  if (node->Folha) {
    return New_node_posicao(node, node->n_Chaves-1);
  }
  else {
    return Find_node_max(node->filhos[node->n_Chaves]);
  }
}

// ------------------------------------------------------------------------------------

Dados* Copy_data(Dados *p) {
  Dados *new = New_data(p->Chave, p->pessoas);         //copia dados
  return new;
}

// ------------------------------------------------------------------------------------

void Delete_node(Nodulo *node) {
  free(node->filhos);
  free(node->Chaves);             //engloba a liberação de espaço de memoria
  free(node);
}