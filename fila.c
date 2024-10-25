#include "fila.h"
#include "erro.h"
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
int fila_vazia(Fila *f) //tem que mudar para bool
{
    if (f==NULL){
        return ERRO1; 
    }
    if (f->inicio == NULL)
    {
        return 1;
    }
    else
        return 0;
}
int fila_push(Fila *f, elem_fila *dado) //Adiciona uma elemento na fila
{
    if (f == NULL)
        return ERRO1;
    FilaBloco *p = (FilaBloco *)malloc(sizeof(FilaBloco));

    if (fila_verifica_elem(f, dado) != NULL)
    {
        return ERRO1;
    }
    if (p == NULL)
        return ERRO1;

    p->dado = (elem_fila *)malloc(sizeof(elem_fila));
    if (p->dado == NULL)
        return ERRO1;

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
}

FilaBloco *fila_pop(Fila *f) // Remove um elemento e o retorna
{
    if (f == NULL || f->inicio == NULL)
    {
        return NULL;
    }

    FilaBloco *p = f->inicio;
    f->inicio = p->proximo;
    f->total--;
    return p;
}
int fila_print(Fila *f /*, int *erro*/) //printa a fila
{
    if (f == NULL || f->inicio == NULL)
        return ERRO1; // erro=0;

    FilaBloco *p = f->inicio;
    while (p != NULL)
    {
        printf("%s\n", p->dado);
        p = p->proximo;
    }
    printf("\n");
}

int fila_libera(Fila *f /*, int *erro*/)
{
    if (f == NULL)
        return ERRO1; // erro=1;

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
FilaBloco *fila_verifica_elem(Fila *f, elem_fila *dado ) //Verifica se tem uma elemento, se o encontar o retorna
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
    }else{
        return NULL; 
    }
}
int fila_total(Fila *f /*, int *erro*/)
{
    if (f==NULL){
        return ERRO1; 
    }
    return f->total;
}

int fila_bloco_print(FilaBloco *filabloco /*, int *erro*/) // Imprimir o dado de um bloco específico da fila
{
    if (filabloco==NULL){
        return ERRO1; 
    }
    printf("%s", filabloco->dado);
}