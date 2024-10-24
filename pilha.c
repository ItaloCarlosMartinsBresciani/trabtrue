#include "pilha.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pilha *pilha_init()
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

void pilha_push(Pilha *pilha, elem *dado)
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
  else
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
  else
  {
    return NULL;
  }
}

void pilha_print(Pilha *pilha)
{
  if (pilha_vazia(pilha))
  {
    // pilha vazia
    printf("Pilha vazia!\n");
    return;
  }
  else
  {
    PilhaBloco *aux = pilha->topo;
    while (aux != NULL)
    {
      printf("%f\n", aux->dado); 
      aux = aux->anterior;       
    }
  }
}
