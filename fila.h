#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

typedef char elem_fila;

typedef struct FilaBloco{
    struct FilaBloco *proximo; 
    elem_fila *dado;
}FilaBloco;

typedef struct{
    FilaBloco *inicio, *fim; 
    int total;
}Fila;

Fila* fila_init();
int fila_vazia(Fila *f);
int fila_push(Fila *f, elem_fila *dado);
FilaBloco *fila_pop(Fila *f);
int fila_print(Fila *fila);
FilaBloco *fila_verifica_elem(Fila*f, elem_fila *dado);
int fila_libera(Fila *f);
int fila_total(Fila *f);
int fila_bloco_print(FilaBloco *filabloco);

#endif