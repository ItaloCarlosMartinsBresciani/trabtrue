#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include "fila.h"
#include "pilha.h"

typedef char elem;

typedef struct ListaBloco
{
    struct ListaBloco *proximo;
    struct ListaBloco *anterior;
    Fila *fila;
    Pilha *pilha;
    elem *dado;
} ListaBloco;

typedef struct Lista
{
    ListaBloco *inicio, *fim;
    int total;
} Lista;

Lista *lista_init();
void lista_push(Lista *lista, elem *dado);
ListaBloco *lista_pop(Lista *lista);
bool lista_vazia(Lista *lista);
// void lista_print_inv(Lista *lista);
void lista_print(Lista *lista);

#endif