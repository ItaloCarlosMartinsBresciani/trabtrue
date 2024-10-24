#include "pilha.h"
#include "bloco.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void pilha_init(Pilha *pilha)
{
  pilha->topo = NULL;
}

bool pilha_vazia(Pilha *pilha){
  if (pilha->topo == NULL)
  {
    return true;
  }else{
    return false;
  }
}


void pilha_push(Pilha *pilha, void *dado, unsigned long tamanho, char *nome)
{
  Bloco *bloco = bloco_alocar(dado, tamanho);
  assert(bloco!=NULL);

  PilhaBloco *pilha_bloco = malloc(sizeof(PilhaBloco));
  assert(pilha_bloco!=NULL);
  Fila *F;
  fila_init(F);

  pilha_bloco->fila = F;
  pilha_bloco->bloco = bloco;

  memcpy(bloco->dado, dado, tamanho);
  
  if (pilha->topo != NULL)
  {
    pilha_bloco->anterior = pilha->topo;
  }
  else
  {
    pilha_bloco->anterior = NULL;
  }
  pilha->topo = pilha_bloco;
  fila_push(F, nome, strlen(nome)+1);
}

PilhaBloco *pilha_pop(Pilha *pilha)
{
  if (pilha_vazia(pilha) == false){
    PilhaBloco *anterior = pilha->topo;
    pilha->topo = pilha->topo->anterior;
    anterior->anterior = NULL;
    return anterior;
  }else{
    return NULL;
  }
}
