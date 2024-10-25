#ifndef LISTA_H // Verifica se LISTA_H não foi definido
#define LISTA_H

#include <stdbool.h>
#include "fila.h" 
#include "pilha.h" 
#include "erro.h"

// Define o tipo elem_lista como char
typedef char elem_lista;

// Estrutura que representa um bloco (nó) da lista
typedef struct ListaBloco
{
    struct ListaBloco *proximo; // Ponteiro para o próximo bloco na lista
    struct ListaBloco *anterior; // Ponteiro para o bloco anterior na lista
    Pilha *pilha; // Ponteiro para uma pilha associada a este bloco
    Fila *fila_usu; // Ponteiro para uma fila associada a este bloco
    elem_lista *dado; // Ponteiro para os dados armazenados neste bloco
} ListaBloco;

// Estrutura que representa a lista
typedef struct Lista
{
    ListaBloco *inicio, *fim; // Ponteiros para o início e o fim da lista
    int total; // Total de elementos na lista
} Lista;

//  Inicializar uma nova lista
Lista *lista_init(tipo_erro *erro);

//  Adicionar um novo elemento na lista
void lista_push(Lista *lista, elem_lista *dado, tipo_erro *erro);

//  Remover e retornar o bloco do fim da lista
ListaBloco *lista_pop(Lista *lista, tipo_erro *erro);

//  Verificar se a lista está vazia
bool lista_vazia(Lista *lista);

//  Imprimir os elementos da lista
int lista_print(Lista *lista);

//  Liberar a memória ocupada pela lista
int lista_libera(Lista *lista);

//  Verificar se um elemento tá presente na lista
ListaBloco *lista_verifica_elem(Lista *lista, elem_lista *dado);

//  Imprimir os dados de um bloco específico da lista
int lista_bloco_print(ListaBloco *listabloco);

#endif