#include "pilha.h"
#include "erro.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Pilha *pilha_init(tipo_erro *erro) //ok
{
  Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
  if(pilha==NULL){
    *erro = ERRO_NULL; // tentou usar ponteiro nulo
    return NULL;
  }
  pilha->topo = NULL;
  *erro = SUCESSO;
  return pilha;
}

bool pilha_vazia(Pilha *pilha, tipo_erro *erro) //ok
{
  if (pilha==NULL){
    *erro = ERRO_NULL;
    return false; 
  }
  if (pilha->topo == NULL)
  {
    *erro = SUCESSO;
    return true;
  }
  else
  {
    *erro = SUCESSO;
    return false;
  }
}

void pilha_push(Pilha *pilha, elem_pilha *dado, elem_fila *nome, tipo_erro *erro)  // Insere uma valor na pilha de lances e inicia uma lista de usuario para cada um
{
  if (pilha==NULL || dado==NULL || nome==NULL){
    *erro = ERRO_NULL;
    return; 
  }
  PilhaBloco *bloco = (PilhaBloco *)malloc(sizeof(PilhaBloco));
  if (bloco==NULL){
    *erro = ERRO_ALLOC; // falha de alocação de memória
    return; 
  }

  Fila *fila;
  bloco->dado = (*dado);
  if (pilha_vazia(pilha, erro))
  {
    pilha->topo = bloco;
    bloco->anterior = NULL;
    fila = fila_init(erro);
    bloco->fila = fila;
    fila_push(fila, nome, erro);
  }
  else if (pilha->topo->dado == (*dado)) // se o lance for igual
  {
    fila_push(pilha->topo->fila, nome, erro);
  }
  else if (pilha->topo->dado < (*dado)) // só empilha se o lance for maior que o topo
  {
    bloco->anterior = pilha->topo;
    pilha->topo = bloco;
    fila = fila_init(erro);
    bloco->fila = fila;
    fila_push(fila, nome, erro);
  }
  *erro = SUCESSO;
}

PilhaBloco *pilha_pop(Pilha *pilha, tipo_erro *erro)
{
  if (pilha==NULL){
    *erro = ERRO_NULL; 
    return NULL;
  }
  if (pilha_vazia(pilha, erro) == false)
  { 
    PilhaBloco *aux = pilha->topo;
    pilha->topo = aux->anterior;
    aux->anterior = NULL;
    *erro = SUCESSO;
    return aux;
  }
}

void pilha_print(Pilha *pilha, tipo_erro *erro)
{
  if(pilha==NULL){
    *erro = ERRO_NULL;
    return; 
  }
  if (!pilha_vazia(pilha, erro))
  {
    PilhaBloco *aux = pilha->topo;
    while (aux != NULL)
    {
      printf("%.2f: ", aux->dado); 
      aux = aux->anterior;
    }
  }
  *erro = SUCESSO;
}

void pilha_libera(Pilha *pilha, tipo_erro *erro)  /*, int *erro*/
{
  if (pilha==NULL){
    *erro = ERRO_NULL;
    return; 
  }
  if (!pilha_vazia(pilha, erro))
  {
    PilhaBloco *p = pilha->topo;
    while (p != NULL)
    {
      PilhaBloco *temp = p;
      p = p->anterior;
      free(temp);
    }
    pilha->topo = NULL;
    *erro = SUCESSO;
  }
  free(pilha);
}

PilhaBloco *pilha_print_topo(Pilha *pilha, tipo_erro *erro)  /*, int *erro*/
{
  if (pilha==NULL){
    *erro = ERRO_NULL;
    return NULL; //erro
  }
  if (pilha_vazia(pilha, erro) == false)
  {
    *erro = SUCESSO;
    return pilha->topo;
  }
}

void pilha_bloco_print(PilhaBloco *pilhabloco, tipo_erro *erro)
{
    if(pilhabloco == NULL){
      *erro = ERRO_NULL; // tentou acessar um bloco nulo
      return;
    }
    printf("%.2f", pilhabloco->dado);
    return;
}