#include "fila.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Fila *fila_init()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    if (f != NULL)
    {
        return;
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
void fila_push(Fila *f, elem *dado)
{
    if (f != NULL)
    { // se a fila existir
        FilaBloco *p = (FilaBloco *)malloc(sizeof(FilaBloco));
        if (p != NULL)
        {
            p->dado = (elem *)malloc(sizeof(elem));
            if (p->dado != NULL)
            {
                memcpy(p->dado, dado, sizeof(elem));
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
                    temp = temp->proximo
                }
                temp->proximo = p;
                p->proximo = NULL;
            }
            f->total++;
        }
        else
        {
            return;
        }
    }
    else
    {
        return;
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
    else
    {
        return;
    }
}
void fila_print(Fila *fila)
{
    if (f != NULL || f->inicio != NULL)
    {
        FilaBloco *p = f->inicio;
        while (p != NULL)
        {
            printf("%s ", p->dado);
            p = p->proximo;
        }
        printf("\n";)
    }
}
void fila_libera(Fila *f)
{
    if (f == NULL)
    {
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
}
/*int fila_verifica_elem(Fila *f, elem *dado){
    if (f==NULL || f->inicio==NULL){
     return;
    }
    FilaBloco *p=f->inicio;

    while(p!=NULL){
        if (strcmp(p->dado, dado)==0) return 1;
    }

    }
*/