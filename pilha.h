#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef float elem;

typedef struct bloco{
  struct bloco *anterior;
  elem dado;
}Pilha_Bloco;

typedef struct pilha{
  Pilha_Bloco *topo;
}Pilha;

void pilha_init(Pilha *pilha);
bool pilha_vazia(Pilha *pilha);
void pilha_push(Pilha *pilha, elem *dado);
void pilha_print(Pilha *pilha);


#endif