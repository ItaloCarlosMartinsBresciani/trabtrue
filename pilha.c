#include "pilha.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

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

void pilha_push(Pilha *pilha, elem_pilha *dado, elem_fila *nome)
{
  PilhaBloco *bloco = (PilhaBloco *)malloc(sizeof(PilhaBloco));

  Fila *fila;
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
    fila = fila_init();
    bloco->fila = fila;
    fila_push(fila, nome);
  }
  else if (pilha->topo->dado == (*dado)) // se o lance for igual
  {
    fila_push(pilha->topo->fila, nome);
  }
  else if (pilha->topo->dado < (*dado)) // só empilha se o lance for maior que o topo
  {
    bloco->anterior = pilha->topo;
    pilha->topo = bloco;
    fila = fila_init();
    bloco->fila = fila;
    fila_push(fila, nome);
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
    // FilaBloco *aux2 = aux->fila->inicio;
    while (aux != NULL)
    {
      if (aux->fila->total > 1){
        printf("\t\t%d lances de R$", aux->fila->total);//total de lançes

      }else{
        printf("\t\t%d lance de R$", aux->fila->total);
      }
      //total de lançes
      printf("%.2f: ", aux->dado);
      fila_print(aux->fila);
      //while (aux2 != NULL)
      //{
      //  printf("%s\n", aux2->dado);
      //  aux2 = aux2->proximo;
      //}
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

PilhaBloco *pilha_print_topo(Pilha *pilha)
{
  if (pilha_vazia(pilha) == false)
  {
    return pilha->topo;
  }
}
