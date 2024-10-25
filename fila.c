#include "fila.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

Fila *fila_init()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    if (f == NULL)
    {
        return NULL;
    }
    f->inicio = NULL;
    f->fim = NULL;
    f->total = 0;
    return f;
}
int fila_vazia(Fila *f)
{
    if (f->inicio == NULL)
    {
        return 1;
    }
    else
        return 0;
}
void fila_push(Fila *f, elem_fila *dado) //fila sem repetição
{
    if (f != NULL)
    { // se a fila existir
        FilaBloco *p = (FilaBloco *)malloc(sizeof(FilaBloco));
        //verificando se o dado a ser colocado na fila já está lá
        if(fila_verifica_elem(f, dado) != NULL){
            return; // sai da função e não faz nada
        }
        if (p != NULL)
        {
            p->dado = (elem_fila *)malloc(sizeof(elem_fila));
            if (p->dado != NULL)
            {
                memcpy(p->dado, dado, strlen(dado)+1);
            }

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
            f->total++;
        }
        
    }
    
}
FilaBloco *fila_pop(Fila *f)
{
    if (f != NULL || f->inicio != NULL)
    {
        FilaBloco *p = f->inicio;
        f->inicio = p->proximo;
        f->total--;
        return p;
    }
    
}
void fila_print(Fila *f)
{
    if (f != NULL || f->inicio != NULL) // Corrigido para usar '&&'
    {
    FilaBloco *p = f->inicio;
    while (p != NULL)
    {        
        printf("%s\n", p->dado);
        p = p->proximo;
    }
    printf("\n");}
}

void fila_libera(Fila *f)
{
    if (f != NULL)
    {
       
    FilaBloco *p = f->inicio;
    while (p != NULL)
    {
        FilaBloco *prox = p->proximo;
        free(p->dado);
        free(p);
        p = prox;
    }
    free(f);}
}
FilaBloco *fila_verifica_elem(Fila *f, elem_fila *dado)
{
    if (f != NULL || f->inicio != NULL)
    {
        
    FilaBloco *p = f->inicio;

    while (p != NULL)
    {
        if (strcmp(p->dado, dado) == 0)
            return p;
        p = p->proximo;
    }
    return NULL;
    }
}
int fila_total(Fila*f){
    return f->total;
}

void fila_bloco_print(FilaBloco *filabloco){
    printf("%s", filabloco->dado);
}