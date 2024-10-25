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
    if (lista==NULL || dado==NULL){ //verifica se a lista existe e o dado existe
        return ERRO1; 
    }
    ListaBloco *Lista_bloco = (ListaBloco *)malloc(sizeof(ListaBloco)); //aloquei um bloco lista
    
    if (Lista_bloco==NULL){ //ve se deu pau
        return ERRO1; 
    }
    Lista_bloco->fila_usu = fila_init(); //inicializei
    Lista_bloco->dado = dado; //campo dado aponta o nome do produto
    
    Pilha *P = pilha_init();
    Lista_bloco->pilha = P;

    ListaBloco *aux, *ant;
    aux = lista->inicio;
    ant = NULL;

    // Navega pela lista até encontrar a posição de inserção
    // ou um elemento igual ao dado

    while (aux != NULL && strcmp(dado, aux->dado) > 0)
    {
        ant = aux;
        aux = aux->proximo;
    }

    // Se o elemento já existe na lista (dado é igual)
    if (aux != NULL && strcmp(dado, aux->dado) == 0)
    {
        free(Lista_bloco);
        return ERRO99;
    }
    // Se estamos inserindo no início da lista (antes do primeiro elemento)
    if (ant == NULL)
    {
        Lista_bloco->proximo = lista->inicio;
        if (lista->inicio != NULL)
            lista->inicio->anterior = Lista_bloco;
        lista->inicio = Lista_bloco;
        lista->fim = Lista_bloco;
    }
    else // Inserção em qualquer lugar depois do primeiro elemento
    {
        Lista_bloco->proximo = ant->proximo;
        ant->proximo = Lista_bloco;
        if (Lista_bloco->proximo != NULL) // Se há um bloco após o novo bloco
            Lista_bloco->proximo->anterior = Lista_bloco;
        else // Se não há próximo, atualiza o final da lista
            lista->fim = Lista_bloco;
        Lista_bloco->anterior = ant;
    }
    return SUCESSO;
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
