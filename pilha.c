#include "pilha.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pilha *pilha_init(void)
{
  Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
  pilha->topo = NULL;
  return pilha;
}

bool pilha_vazia(Pilha *pilha)
{
  if (pilha->topo == NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void pilha_push(Pilha *pilha, elem_pilha *dado)
{
  PilhaBloco *bloco = (PilhaBloco *)malloc(sizeof(PilhaBloco));
  if (bloco == NULL)
  {
    // erro de alocação de memória
    return;
  }
  bloco->dado = (*dado);
  if (pilha_vazia(pilha))
  {
    pilha->topo = bloco;
    bloco->anterior = NULL;
  }
  else if (pilha->topo->dado < (*dado))
  {
    bloco->anterior = pilha->topo;
    pilha->topo = bloco;
  }
}

PilhaBloco *pilha_pop(Pilha *pilha)
{
  if (pilha_vazia(pilha) == false)
  {
    PilhaBloco *aux = pilha->topo;
    pilha->topo = aux->anterior;
    aux->anterior = NULL;
    return aux;
  }
}

void pilha_print(Pilha *pilha)
{
  if (!pilha_vazia(pilha))
  {
    PilhaBloco *aux = pilha->topo;
    while (aux != NULL)
    {
      printf("%f\n", aux->dado);
      aux = aux->anterior;
    }
  }
}
void pilha_libera(Pilha *pilha)
{
  if (!pilha_vazia(pilha))
  {
    PilhaBloco *p = pilha->topo;
    while (p != NULL)
    {
      PilhaBloco *temp = p;
      p = p->anterior;
      free(temp);
    }
    pilha->topo = NULL;
  }
  free(pilha);
}

void pilha_print_topo(Pilha *pilha)
{
  if (!pilha_vazia(pilha)) printf("%f\n", pilha->topo->dado);
}
