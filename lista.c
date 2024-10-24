#include "lista.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Lista *lista_init()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->fim = NULL;
    lista->inicio = NULL;
    return lista;
}

bool lista_vazia(Lista *lista)
{
    if (lista->inicio == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

ListaBloco *lista_pop(Lista *lista)
{
    if (lista_vazia(lista) == true)
    {
        return NULL;
    }
    else
    {
        ListaBloco *aux = lista->inicio;
        if (lista->inicio == lista->fim)
        {
            lista->inicio = NULL;
            lista->fim = NULL;
        }
        else
        {
            lista->inicio = lista->inicio->proximo;
            lista->inicio->anterior = NULL;
        }
        // aux->pilha=NULL;
        return aux;
    }
}

void lista_print(Lista *lista) //está printando apenas o ultimo elemento da lista
{
    if (lista_vazia(lista)) {
        printf("Lista vazia.\n");
        return;
    }

    ListaBloco *bloco = lista->inicio; // Começa pelo início da lista

    while (bloco != NULL) 
    {
        elem_lista *valor = bloco->dado;
        printf("%s\n", valor); // Imprime o valor atual
        bloco = bloco->proximo; // Avança para o próximo bloco
    }
}

void lista_push(Lista *lista, elem_lista *dado)
{
    ListaBloco *Lista_bloco = (ListaBloco *)malloc(sizeof(ListaBloco));
    assert(Lista_bloco != NULL);

    Lista_bloco->dado = dado;

    ListaBloco *aux, *ant;
    aux = lista->inicio;
    ant = NULL;

    while (aux != NULL && strcmp(dado, aux->dado) > 0)
    {
        ant = aux;
        aux = aux->proximo;
    }
    if (aux != NULL && strcmp(dado, aux->dado) == 0)
    {
        free(Lista_bloco);
        return;
    }
    if (ant == NULL)
    {
        Lista_bloco->proximo = lista->inicio;
        if (lista->inicio != NULL)
            lista->inicio->anterior = Lista_bloco;
        lista->inicio = Lista_bloco;
    }
    else
    {
        Lista_bloco->proximo = ant->proximo;
        ant->proximo = Lista_bloco;
        if (Lista_bloco->proximo != NULL)
            Lista_bloco->proximo->anterior = Lista_bloco;
        else
            lista->fim = Lista_bloco;
        Lista_bloco->anterior = ant;
    }
}