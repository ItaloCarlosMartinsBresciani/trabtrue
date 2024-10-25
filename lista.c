#include "lista.h"
#include "erro.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

Lista *lista_init(tipo_erro *erro)  //ok
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    if (lista==NULL){
        *erro = ERRO_ALLOC; // erro de alocação de memória
        return NULL; 
    }
    lista->fim = NULL;
    lista->inicio = NULL;
    *erro = SUCESSO; // lista inicializada com sucesso
    return lista;  
}

bool lista_vazia(Lista *lista, tipo_erro *erro)  /*, int *erro*/
{
    if (lista == NULL){ //verifica se a lista existe
        *erro = ERRO_NULL; // tentou usar um ponteiro nulo
        return false; 
    }
    if (lista->inicio == NULL)
    {
        *erro = SUCESSO; // verificação ok
        return true;
    }
    else
    {
        *erro = SUCESSO; // verificação ok
        return false;
    }
}

ListaBloco *lista_pop(Lista *lista, tipo_erro *erro)  /*, int *erro*/
{
    if (lista==NULL){ //verifica se a lista existe
        *erro = ERRO_NULL;
        return NULL; 
    }
    if (lista_vazia(lista, erro)==true)
    {
        if(erro != SUCESSO) // significa que a verificação se a lista está vazia não deu certo
        {
            return NULL;
        }
        *erro = ERRO_POP_VAZIO; // tentou inserir elemento em uma lista vazia
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

    *erro = SUCESSO;
    return bloco_removido;
}

void lista_print(Lista *lista, tipo_erro *erro)  /*, int *erro*/
{
    if (lista==NULL){
        *erro = ERRO_NULL; // tentou usar ponteiro
        return; 
    }
    if (!lista_vazia(lista, erro))
    {
        if(erro != SUCESSO) // verificação de lista vazia não funcionou (ERRO_NULL)
        {
            return;
        }
        ListaBloco *bloco = lista->inicio;

        while (bloco != NULL)
        {
            printf("\t%s\n", bloco->dado);
            bloco = bloco->proximo;
        }
    }
    *erro = SUCESSO;
}

void lista_push(Lista *lista, elem_lista *dado, tipo_erro *erro)  /*, int *erro*/
{
    if (lista==NULL || dado==NULL){ //verifica se a lista existe e o dado existe
        *erro = ERRO_NULL; // foi passado um ponteiro nulo para a função lista_push
        return; 
    }
    ListaBloco *Lista_bloco = (ListaBloco *)malloc(sizeof(ListaBloco)); //aloquei um bloco lista
    
    if (Lista_bloco==NULL){ 
        *erro = ERRO_ALLOC; // erro de alocação de memória
        return; 
    }
    Lista_bloco->fila_usu = fila_init(erro); //inicializei
    Lista_bloco->dado = dado; //campo dado aponta o nome do produto
    
    Pilha *P = pilha_init(erro);
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
        *erro = ERRO_ELEM_REPETIDO; // Um elemento repetido foi tentar usar 
        return; 
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
    *erro = SUCESSO;
}

void lista_libera(Lista *lista, tipo_erro *erro) 
{
    if (lista==NULL){
        *erro = ERRO_NULL; // tentou usar um ponteiro nullo
        return; 
    }
    ListaBloco *bloco = lista->inicio;

    while (bloco != NULL)
    {
        ListaBloco *prox = bloco->proximo;
        free(bloco);
        bloco = prox;
    }
    free(lista); // Libera a lista após liberar todos os blocos
    *erro = SUCESSO;
}
ListaBloco *lista_verifica_elem(Lista *lista, elem_lista *dado, tipo_erro *erro)
{
    if (lista==NULL || dado==NULL){
        *erro = ERRO_NULL;
        return NULL; //erro
    }
    if (!lista_vazia(lista, erro))
    {
        if(*erro != SUCESSO) // verificação de lista vazia não funcionou (ERRO_NULL)
        {
            return NULL;
        }
        
        ListaBloco *no = lista->inicio;
        while (no != NULL)
        {
            if (strcmp(no->dado, dado) == 0)
            {
                *erro = SUCESSO;
                return no;
            }
            no = no->proximo;
        }
    }
    *erro = SUCESSO;
    return NULL;
}

void lista_bloco_print(ListaBloco *listabloco, tipo_erro *erro)  /*, int *erro*/
{
    if (listabloco==NULL){
        *erro = ERRO_NULL; // tentou usar ponteiro nulo
        return; 
    }
    printf("%s", listabloco->dado);
    *erro = SUCESSO;
}
