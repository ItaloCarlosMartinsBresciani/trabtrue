#ifndef PILHA_H
#define PILHA_H

#include "fila.h"
#include <stdbool.h>

typedef float elem_pilha;

typedef struct PilhaBloco{
  struct PilhaBloco *anterior;
  elem_pilha dado; 
  Fila *fila;
}PilhaBloco;

typedef struct pilha{
  PilhaBloco *topo;
}Pilha;

Pilha *pilha_init(void);
bool pilha_vazia(Pilha *pilha);
void pilha_push(Pilha *pilha, elem_pilha *dado, elem_fila *nome);
PilhaBloco *pilha_pop(Pilha *pilha);
void pilha_print(Pilha *pilha);
void pilha_libera(Pilha *pilha);
//pilha_verifica_elem
PilhaBloco *pilha_print_topo(Pilha *pilha);
#endif