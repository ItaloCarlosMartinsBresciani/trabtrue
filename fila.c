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
void fila_push(Fila *f, elem_fila *dado)
{
    if (f != NULL)
    { // se a fila existir
        FilaBloco *p = (FilaBloco *)malloc(sizeof(FilaBloco));
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
        if (p->proximo == f->fim){
            printf("%s ", p->dado);
        }else{
            printf("%s, ", p->dado);
        }
        
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

void push_fila_usuario(Fila *F, elem_fila *dado){ //fila de usuarios sem repetição

    if (!fila_vazia(F)){  //se tiver vazia
        fila_push(F,dado); //dá um push na fila
    }else{
        if (fila_verifica_elem(F,dado)==NULL){ //verifica se o dado já está na fila
            fila_push(F,dado); //só dá um push se não tiver
        }
    }
}

void fila_bloco_print(FilaBloco *filabloco){
    printf("%s", filabloco->dado);
}