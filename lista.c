#include "bloco.h"
#include "pilha.h"
#include "lista.h"
#include <stdio.h>
#include <locale.h> 
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void lista_init(Lista *lista)
{
    if (lista!=NULL){
    lista->inicio = NULL;
    lista->fim = NULL;
    }
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
        aux->pilha=NULL;
        return aux;
    }
}

void lista_print(Lista *lista)
{
    printf("entrou lista_print");
    assert(lista != NULL);
    ListaBloco *aux = lista->inicio;
    PilhaBloco *aux2 = aux->pilha->topo;
    FilaBloco *aux3 = aux2->fila->inicio;
    printf("minipulou os blocos legal");
    
    while (aux != NULL)
    {
        printf("%s\n", aux->bloco->dado);
        while(aux2 != NULL){
            printf("%s\n", aux2->bloco->dado);
            while (aux3 != NULL){
                printf("%s\n", aux3->bloco->dado);
                aux3 = aux3->proximo;
            }
            aux2 = aux2->anterior;
        }
        aux = aux->proximo;
    } 
}

void lista_print_inv(Lista *lista)
{
    assert(lista != NULL);
    ListaBloco *aux = lista->fim;
    PilhaBloco *aux2 = aux->pilha->topo;
    while (aux != NULL)
    {
        printf("%s\n", aux->bloco->dado);
        while(aux2 != NULL){
            printf("%s\n", aux2->bloco->dado);
            aux2 = aux2->anterior;
        }
        aux = aux->proximo;
    }
}

void lista_push(Lista *lista, void *dado, unsigned long tamanho)
{
    Bloco *B = bloco_alocar(dado, tamanho);
    assert(B != NULL);

    ListaBloco *Lista_bloco = (ListaBloco *)malloc(sizeof(ListaBloco));
    assert(Lista_bloco != NULL);

    Pilha *P; //criamos uma pilha de lances ligado a cada produto (listabloco)
    pilha_init(P);

    Lista_bloco->pilha= P;
    Lista_bloco->bloco = B;

    ListaBloco *aux, *ant;
    aux = lista->inicio;
    ant = NULL;

    while (aux != NULL && strcmp(dado, aux->bloco->dado) > 0)
    {
        ant = aux;
        aux = aux->proximo;
    }
    if (aux != NULL && strcmp(dado, aux->bloco->dado) == 0)
    {
        free(B);
        free(Lista_bloco);
        return;
    }
    if (ant == NULL)
    {
        Lista_bloco->proximo = lista->inicio;
        if (lista->inicio != NULL) lista->inicio->anterior = Lista_bloco;
        lista->inicio = Lista_bloco;
    }else{
        Lista_bloco->proximo = ant->proximo;
        ant->proximo = Lista_bloco;
        if (Lista_bloco->proximo != NULL ) Lista_bloco->proximo->anterior = Lista_bloco;
        else lista->fim = Lista_bloco;
        Lista_bloco->anterior = ant;
    }
}