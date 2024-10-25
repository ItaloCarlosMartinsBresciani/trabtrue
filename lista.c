#include "lista.h"
#include "erro.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Lista *lista_init()  //ok
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    if (lista==NULL){
        return NULL;
    }
    lista->fim = NULL;
    lista->inicio = NULL;
    return lista;
}

bool lista_vazia(Lista *lista)  /*, int *erro*/
{
    if (lista==NULL){ //verifica se a lista existe
        return ERRO1; 
    }
    if (lista->inicio == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

ListaBloco *lista_pop(Lista *lista)  /*, int *erro*/
{
    if (lista==NULL){ //verifica se a lista existe
        return NULL; 
    }
    if (lista_vazia(lista)==true)
    {
        return NULL;
    }

    ListaBloco *bloco_removido = lista->fim;

    if (lista->inicio == lista->fim)
    {
        lista->inicio = NULL;
        lista->fim = NULL;
    }
    else
    {
        lista->fim = lista->fim->anterior;
        lista->fim->proximo = NULL;
    }

    return bloco_removido;
}
int lista_print(Lista *lista)  /*, int *erro*/
{
    if (lista==NULL){
        return ERRO1; 
    }
    if (!lista_vazia(lista))
    {
        ListaBloco *bloco = lista->inicio;

        while (bloco != NULL)
        {
            printf("\t%s\n", bloco->dado);
            bloco = bloco->proximo;
        }
    }
}

int lista_push(Lista *lista, elem_lista *dado)  /*, int *erro*/
{
    if (lista==NULL || dado==NULL){
        return ERRO1; 
    }
    ListaBloco *Lista_bloco = (ListaBloco *)malloc(sizeof(ListaBloco));
    if (Lista_bloco==NULL){
        return ERRO1; 
    }
    Lista_bloco->fila_usu=NULL;
    Lista_bloco->dado = dado;
    Pilha *P = pilha_init();
    Lista_bloco->pilha = P;

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
        return SUCESSO;
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

int lista_libera(Lista *lista)  /*, int *erro*/
{
    if (lista==NULL){
        return ERRO1; 
    }
    ListaBloco *bloco = lista->inicio;

    while (bloco != NULL)
    {
        ListaBloco *prox = bloco->proximo;
        free(bloco);
        bloco = prox;
    }

    free(lista); // Libera a lista após liberar todos os blocos
}
ListaBloco *lista_verifica_elem(Lista *lista, elem_lista *dado)  /*, int *erro*/
{
    if (lista==NULL || dado==NULL){
        return NULL; //erro
    }
    if (!lista_vazia(lista))
    {
        ListaBloco *no = lista->inicio;
        while (no != NULL)
        {
            if (strcmp(no->dado, dado) == 0)
            {
                return no;
            }
            no = no->proximo;
        }
    }
    return NULL;
}

int lista_bloco_print(ListaBloco *listabloco)  /*, int *erro*/
{
    if (listabloco==NULL){
        return ERRO1; 
    }
    printf("%s", listabloco->dado);
}
