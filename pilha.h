#ifndef PILHA_H
#define PILHA_H

#include "fila.h"
#include <stdbool.h>

typedef char elem;

typedef struct PilhaBloco{
  struct PilhaBloco *anterior;
  elem dado;
}PilhaBloco;

typedef struct pilha{
  PilhaBloco *topo;
}Pilha;

Pilha *pilha_init();
bool pilha_vazia(Pilha *pilha);
void pilha_push(Pilha *pilha, elem *dado);
void pilha_print(Pilha *pilha);


#endif