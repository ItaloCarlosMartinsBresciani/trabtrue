#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include "fila.h"
#include "pilha.h"

typedef char elem_lista;

typedef struct ListaBloco
{
    struct ListaBloco *proximo;
    struct ListaBloco *anterior;
    Pilha *pilha;
    Fila *fila_usu;
    elem_lista *dado;
} ListaBloco;

typedef struct Lista
{
    ListaBloco *inicio, *fim;
    int total;
} Lista;

Lista *lista_init();
int lista_push(Lista *lista, elem_lista *dado);
ListaBloco *lista_pop(Lista *lista);
bool lista_vazia(Lista *lista);
// void lista_print_inv(Lista *lista);
int lista_print(Lista *lista);
int lista_libera(Lista *lista);
ListaBloco *lista_verifica_elem(Lista *lista, elem_lista *dado);
int lista_bloco_print(ListaBloco *listabloco);

#endif