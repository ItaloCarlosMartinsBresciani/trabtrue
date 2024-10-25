#ifndef PILHA_H // Verifica se PILHA_H não foi definido
#define PILHA_H

#include "erro.h"
#include "fila.h"
#include <stdbool.h> 

// Define o tipo elem_pilha como float
typedef float elem_pilha;

// Estrutura que representa um bloco (nó) da pilha
typedef struct PilhaBloco{
  struct PilhaBloco *anterior; // Ponteiro para o bloco anterior na pilha
  elem_pilha dado; // Dado armazenado neste bloco da pilha
  Fila *fila; // Ponteiro para uma fila associada a este bloco
} PilhaBloco;

// Estrutura que representa a pilha
typedef struct pilha{
  PilhaBloco *topo; // Ponteiro para o topo da pilha
} Pilha;

//  Inicializar uma nova pilha
Pilha *pilha_init(tipo_erro *erro); //erro implement

//  Verificar se a pilha está vazia
bool pilha_vazia(Pilha *pilha, tipo_erro *erro); //erro implement

//  Adicionar um novo elemento ao topo da pilha
void pilha_push(Pilha *pilha, elem_pilha *dado, elem_fila *nome, tipo_erro *erro);

//  Remover e retornar o bloco do topo da pilha
PilhaBloco *pilha_pop(Pilha *pilha, tipo_erro *erro);

//  Imprimir os elementos da pilha
void pilha_print(Pilha *pilha, tipo_erro *erro);

//  Liberar a memória ocupada pela pilha
void pilha_libera(Pilha *pilha, tipo_erro *erro);

//  Imprimir os dados de um bloco específico da pilha
void pilha_bloco_print(PilhaBloco *pilhabloco, tipo_erro *erro);

//  Retornar o bloco do topo da pilha
PilhaBloco *pilha_print_topo(Pilha *pilha, tipo_erro *erro);

#endif