#include "fila.h"
#include "erro.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


Fila *fila_init(tipo_erro *erro)
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    if (f == NULL)
    {
        *erro = ERRO_ALLOC;
        return NULL;
    }
    f->inicio = NULL;
    f->fim = NULL;
    f->total = 0;
    *erro = SUCESSO;
    return f;
}
bool fila_vazia(Fila *f, tipo_erro *erro) //tem que mudar para bool
{
    if (f==NULL){
        *erro = ERRO_NULL;
        return false; 
    }
    if (f->inicio == NULL)
    {
        *erro = SUCESSO;
        return true;
    }
    else{
        *erro = SUCESSO;
        return false;
    }
}
void fila_push(Fila *f, elem_fila *dado, tipo_erro *erro) //Adiciona uma elemento na fila
{
    if (f == NULL){
        *erro = ERRO_NULL;
        return;
    }
    FilaBloco *p = (FilaBloco *)malloc(sizeof(FilaBloco));
    
    if (p==NULL){
        *erro = ERRO_ALLOC; // erro de alocação de memória
        return; 
    }

    if (fila_verifica_elem(f, dado, erro) != NULL)
    {
        *erro = ERRO_ELEM_REPETIDO;
        return;
    }

    p->dado = (elem_fila *)malloc(sizeof(elem_fila));
    if (p->dado == NULL){
        *erro = ERRO_NULL;
        return;
    }

    memcpy(p->dado, dado, strlen(dado) + 1);

    if (f->inicio == NULL)
    {
        f->inicio = p;
        p->proximo = NULL;
    }
    else
    {
        FilaBloco *temp = f->inicio;
        while (temp->proximo != NULL)
        {
            temp = temp->proximo;
        }
        temp->proximo = p;
        p->proximo = NULL;
    }
    f->fim=p;
    f->total++;
    *erro = SUCESSO;
}

FilaBloco *fila_pop(Fila *f, tipo_erro *erro) // Remove um elemento e o retorna
{
    if (f == NULL || f->inicio == NULL)
    {
        *erro = ERRO_NULL;
        return NULL;
    }

    FilaBloco *p = f->inicio;
    f->inicio = p->proximo;
    f->total--;
    *erro = SUCESSO;
    return p;
}
void fila_print(Fila *f, tipo_erro *erro) //printa a fila
{
    if (f == NULL || f->inicio == NULL){
        *erro = ERRO_NULL;
        return;
    }

    FilaBloco *p = f->inicio;
    while (p != NULL)
    {
        printf("%s\n", p->dado);
        p = p->proximo;
    }
    *erro = SUCESSO;
    printf("\n");
}

void fila_libera(Fila *f, tipo_erro *erro)
{
    if (f == NULL){
        *erro = ERRO_NULL;
        return;
    }

    FilaBloco *p = f->inicio;
    while (p != NULL)
    {
        FilaBloco *prox = p->proximo;
        free(p->dado);
        free(p);
        p = prox;
    }
    free(f);
    *erro = SUCESSO;
}
FilaBloco *fila_verifica_elem(Fila *f, elem_fila *dado, tipo_erro *erro) //Verifica se tem uma elemento, se o encontar o retorna
{
    if (f != NULL || f->inicio != NULL)
    {
        FilaBloco *p = f->inicio;

        while (p != NULL)
        {
            if (strcmp(p->dado, dado) == 0){
                *erro = SUCESSO;
                return p;
            }
            p = p->proximo;
        }
        
        return NULL;
    }else{
        *erro = ERRO_NULL; // tentou acessar um ponteiro nulo ou dado nulo
        return NULL; 
    }
}
int fila_total(Fila *f, tipo_erro *erro)
{
    if (f==NULL){
        *erro = ERRO_NULL;
        return 0;
    }
    *erro = SUCESSO;
    return f->total;
}

void fila_bloco_print(FilaBloco *filabloco, tipo_erro *erro) // Imprimir o dado de um bloco específico da fila
{
    if (filabloco==NULL){
        *erro = ERRO_NULL;
        return; 
    }
    *erro = SUCESSO;
    printf("%s", filabloco->dado);
}