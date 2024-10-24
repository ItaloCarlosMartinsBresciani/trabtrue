#ifndef PILHA_H
#define PILHA_H

#include "fila.h"
#include <stdbool.h>

typedef float elem_pilha;

typedef struct PilhaBloco{
  struct PilhaBloco *anterior;
  elem_pilha dado;
}PilhaBloco;

typedef struct pilha{
  PilhaBloco *topo;
}Pilha;

Pilha *pilha_init();
bool pilha_vazia(Pilha *pilha);
void pilha_push(Pilha *pilha, elem_pilha *dado);
void pilha_print(Pilha *pilha);
//pilha_libera
//pilha_verifica_elem


#endif