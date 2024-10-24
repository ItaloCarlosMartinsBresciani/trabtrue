#ifndef FILA_H
#define FILA_H

//filas (de usuários que deram cada lance, por produto)
#include "bloco.h"

typedef struct FilaBloco{
    struct FilaBloco *proximo; 
    Bloco *bloco;
}FilaBloco;

typedef struct{
    FilaBloco *inicio, *fim; 
    int total;
}Fila;

void fila_init(Fila *fila);
int fila_vazia(Fila *f);
void fila_push(Fila *f, void *dado, unsigned long tamanho);
FilaBloco *fila_pop(Fila *f);
void fila_print(Fila *fila);

#endif