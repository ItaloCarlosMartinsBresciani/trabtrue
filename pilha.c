#include "pilha.h"
#include "erro.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Pilha *pilha_init(void) //ok
{
  Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
  if(pilha==NULL){
    return NULL;
  }
  pilha->topo = NULL;
  return pilha;
}

bool pilha_vazia(Pilha *pilha) //ok
{
  if (pilha==NULL){
    return ERRO1; 
  }
  if (pilha->topo == NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int pilha_push(Pilha *pilha, elem_pilha *dado, elem_fila *nome)  // Insere uma valor na pilha de lances e inicia uma lista de usuario para cada um
{
  if (pilha==NULL || dado==NULL || nome==NULL){
    return ERRO1; 
  }
  PilhaBloco *bloco = (PilhaBloco *)malloc(sizeof(PilhaBloco));
  if (bloco==NULL){
    return ERRO1; 
  }

  Fila *fila;
  
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
  if (pilha==NULL){
    return NULL;
  }
  if (pilha_vazia(pilha) == false)
  {
    PilhaBloco *aux = pilha->topo;
    pilha->topo = aux->anterior;
    aux->anterior = NULL;
    return aux;
  }
}

int pilha_print(Pilha *pilha)
{
  if(pilha==NULL){
    return ERRO1; 
  }
  if (!pilha_vazia(pilha))
  {
    PilhaBloco *aux = pilha->topo;
    while (aux != NULL)
    {
      printf("%.2f: ", aux->dado); 
      aux = aux->anterior;
    }
  }
}

int pilha_libera(Pilha *pilha)  /*, int *erro*/
{
  if (pilha==NULL){
    return ERRO1; 
  }
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

PilhaBloco *pilha_print_topo(Pilha *pilha)  /*, int *erro*/
{
  if (pilha==NULL){
    return NULL; //erro
  }
  if (pilha_vazia(pilha) == false)
  {
    return pilha->topo;
  }
}

int pilha_bloco_print(PilhaBloco *pilhabloco){
    printf("%.2f", pilhabloco->dado);
}